#include "scene.hpp"
#include "node.hpp"

#include <algorithm>
#include <cstddef>
#include <format>
#include <memory>
#include <mutex>
#include <utility>

void Scene::_init() {
    size_t index = 0;

    for (auto &node : _nodes) {
        if (node == nullptr) [[unlikely]] {
            _nodes.erase(_nodes.begin() + static_cast<long long>(index));
        } else {
            node->_init();
            node->setActive(true);
        }

        index++;
    }
}

void Scene::_update() {
    size_t index = 0;

    for (auto &node : _nodes) {
        try {
            if (node == nullptr) [[unlikely]] {
                _nodes.erase(_nodes.begin() + static_cast<long long>(index++));
                continue;
            }

            if (node->_is_active && node->_is_updating) {
                node->_update();
            }
        } catch (const std::exception &e) {
            ErrorCtx("Scene updating")
                .failFallback(std::format("Exception in node '{}': {}", node->_name, e.what()));
        }

        index++;
    }
}

void Scene::_fixedUpdate() {
    for (auto &node : _nodes) {
        try {
            if (node->_is_active && node->_is_fixed_updating) {
                node->_fixedUpdate();
            }
        } catch (const std::exception &e) {
            ErrorCtx("Scene fixed updating")
                .failFallback(std::format("Exception in node '{}': {}", node->_name, e.what()));
        }
    }
}

void Scene::addNode(std::unique_ptr<Node> node) {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Add node '{}' to scene", node->_name));

    if (node == nullptr) [[unlikely]] {
        err.failFallback("Null pointer provided");
        return;
    }

    for (const auto &node_it : _nodes) {
        if (node_it->_name == node->_name) [[unlikely]] {
            err.failFallback("Node with name already exists");
            return;
        }
    }

    DULL_INFO("Added node '{}' to scene.", node->_name);
    _nodes.emplace_back(std::move(node));
}

void Scene::removeNodeByIndex(size_t index) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (index >= _nodes.size()) {
        ErrorCtx("Remove node by index").failFallback("Index out of range");
        return;
    }

    _nodes[index]->setActive(false);
    _nodes.erase(_nodes.begin() + static_cast<long long>(index));
}

void Scene::removeNodeByName(std::string_view name) {
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = std::ranges::find_if(_nodes, [name](const auto &node) { return node->_name == name; });

    if (it == _nodes.end()) {
        ErrorCtx("Remove node by name").failFallback("Not found");
        return;
    }

    _nodes.erase(it);
}

[[nodiscard]] std::weak_ptr<Node> Scene::getNodeByIndex(size_t index) {
    std::lock_guard<std::mutex> lock(_mutex);
    if (index >= _nodes.size()) {
        ErrorCtx("Get node by index").failFallback("Index out of range");
        return {};
    }

    return _nodes[index];
}

[[nodiscard]] std::weak_ptr<Node> Scene::getNodeByName(std::string_view name) {
    std::lock_guard<std::mutex> lock(_mutex);
    auto it = std::ranges::find_if(_nodes, [name](const auto &node) { return node->_name == name; });

    if (it == _nodes.end()) {
        ErrorCtx("Get node by name").failFallback("Not found");
        return {};
    }

    return *it;
}