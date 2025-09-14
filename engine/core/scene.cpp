#include "app/constants.hpp"

#include "engine/core/scene.hpp"
#include "engine/core/app.hpp"
#include "engine/core/node.hpp"
#include "engine/utils/debug.hpp"

#include <cstddef>
#include <cstdint>
#include <format>
#include <memory>
#include <mutex>
#include <utility>

void Scene::_init() {
	size_t index { 0 };

	for (auto& node : _nodes) {
		if (node == nullptr) [[unlikely]] {
			_nodes.erase(_nodes.begin() + static_cast<int64_t>(index));
		} else {
			node->_init();
			node->is_active = true;
		}

		index++;
	}
}

void Scene::_update() {
	size_t index { 0 };

	for (auto& node : _nodes) {
		try {
			if (node == nullptr) [[unlikely]] {
				_nodes.erase(_nodes.begin() + static_cast<long long>(index++));
				continue;
			}

			if (node->is_active && node->is_updating) node->_update();

		} catch (const std::exception& ERR) {
			ErrorCtx{"Scene updating"}.failFallback(
				std::format("Exception in node '{}': {}", node->_name, ERR.what())
			);
		}

		index++;
	}
}

void Scene::_fixedUpdate() {
	for (auto& node : _nodes) {
		try {
			if (node->is_active && node->is_fixed_updating) node->_fixedUpdate();

		} catch (const std::exception& ERR) {
			ErrorCtx{"Scene fixed updating"}.failFallback(
				std::format("Exception in node '{}': {}", node->_name, ERR.what())
			);
		}
	}
}

[[nodiscard]] size_t Scene::nodeIDFromName(std::string_view name) {
	std::lock_guard<std::mutex> lock(_mutex);

	for (size_t i { 0 }; i < _nodes.size(); i++) {
		if (_nodes[i]->name() == name) return i;
	}

	ErrorCtx{"Get node id from name"}.failExit("Name not found");
}

void Scene::addNode(std::unique_ptr<Node> node) noexcept {
	std::lock_guard<std::mutex> lock(_mutex);
	ErrorCtx err{std::format("Add node '{}' to scene", node->_name)};

	if (node == nullptr) [[unlikely]] {
		err.failFallback("Null pointer provided");
		return;
	}

	for (const auto& NODE_IT : _nodes) {
		if (NODE_IT->_name == node->_name) [[unlikely]] {
			err.failFallback("Node with name already exists");
			return;
		}
	}

	// Takes ownership of node and converts it to shared_ptr
	DULL_INFO("Added node '{}' to scene.", node->_name);
	_nodes.emplace_back(std::shared_ptr<Node>(std::move(node)));
}

void Scene::removeNode(size_t node_id) {
	std::lock_guard<std::mutex> lock(_mutex);

	if (node_id > _nodes.size()) {
		ErrorCtx{"Remove node"}.failFallback("Index out of range");
		return;
	}

	DULL_INFO("Added node '{}' to scene.", _nodes[node_id]->name());
	_nodes.erase(_nodes.begin() + node_id);
}

std::weak_ptr<Node> Scene::getNode(size_t node_id) {
	std::lock_guard<std::mutex> lock(_mutex);

	if (node_id > _nodes.size()) {
		ErrorCtx{"Get node"}.failExit("Index out of range");
	}

	return _nodes[node_id];
}

[[nodiscard]] SceneBuilder& SceneBuilder::newScene(size_t node_buffer_size) noexcept {
	_scene = std::make_unique<Scene>(node_buffer_size);
	_scene_node_buffer_size = node_buffer_size;

	return *this;
}

GameInfo::SceneID SceneBuilder::pushToSystem(GameInfo::SceneID scene_id, bool is_startup_scene) noexcept {
	if (_scene == nullptr)
		ErrorCtx{"Push scene to system"}.failExit("Scene not yet initialized");

	SCENE_SYS.addScene(scene_id, std::move(_scene));
	if (is_startup_scene) SCENE_SYS.setCurrent(scene_id);

	_scene = nullptr;
	_scene_node_buffer_size = 0;

	return scene_id;
}