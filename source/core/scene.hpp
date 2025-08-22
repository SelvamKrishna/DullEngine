#pragma once

#include "../utils/debug.hpp"
#include "constants.hpp"
#include "node.hpp"

#include <algorithm>
#include <cstddef>
#include <memory>
#include <mutex>
#include <string_view>
#include <type_traits>
#include <vector>
#include <format>

class Scene {
    friend class App;
    friend class SceneSystem;

private:
    mutable std::mutex _mutex;
    std::vector<std::shared_ptr<Node>> _nodes;

    void _init();
    void _update();
    void _fixedUpdate();

public:
    static constexpr size_t DEFAULT_NODE_BUFFER_SIZE = 16;

    explicit Scene(size_t node_buffer_size = DEFAULT_NODE_BUFFER_SIZE) noexcept {
        _nodes.reserve(node_buffer_size);
    }

    ~Scene() noexcept { clear(); }

    Scene(const Scene&) = delete;
    Scene(Scene&&) = delete;
    Scene& operator=(const Scene&) = delete;
    Scene& operator=(Scene&&) = delete;

    void addNode(std::unique_ptr<Node> node) noexcept;
    void removeNodeByIndex(size_t index) noexcept;
    void removeNodeByName(std::string_view name) noexcept;

    template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
    void removeNode() noexcept {
        std::lock_guard<std::mutex> lock(_mutex);

        auto it = std::ranges::find_if(
            _nodes, [](const auto &node) { return dynamic_cast<NodeT*>(node.get()) != nullptr; }
        );

        if (it == _nodes.end()) {
            ErrorCtx("Remove node by type")
                .failFallback(std::format("Type <{}> Not found", typeid(NodeT).name()));
            return;
        }

        _nodes.erase(it);
    }

    [[nodiscard]] size_t nodeCount() const noexcept { return _nodes.size(); }
    [[nodiscard]] std::weak_ptr<Node> getNodeByIndex(size_t index) noexcept;
    [[nodiscard]] std::weak_ptr<Node> getNodeByName(std::string_view name) noexcept;

    template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
    [[nodiscard]] std::weak_ptr<NodeT> getNode() noexcept {
        std::lock_guard<std::mutex> lock(_mutex);

        auto it = std::ranges::find_if(
            _nodes, [](const auto &node) { return dynamic_cast<NodeT*>(node.get()) != nullptr; }
        );

        if (it == _nodes.end()) {
            ErrorCtx("Get node by type")
                .failFallback(std::format("Type <{}> Not found", typeid(NodeT).name()));
            return {};
        }

        return std::static_pointer_cast<NodeT>(*it);
    }

    void clear() noexcept {
        for (auto &node : _nodes) node.reset();
        _nodes.clear();
    }
};

class SceneBuilder {
private:
    std::unique_ptr<Scene> _scene;
    size_t _scene_node_buffer_size;

public:
    explicit SceneBuilder(size_t scene_node_buffer_size = Scene::DEFAULT_NODE_BUFFER_SIZE)
        : _scene(std::make_unique<Scene>(scene_node_buffer_size))
        , _scene_node_buffer_size(scene_node_buffer_size) {}

    ~SceneBuilder() = default;

    SceneBuilder(const SceneBuilder&) = delete;
    SceneBuilder(SceneBuilder&&) = delete;
    SceneBuilder& operator=(const SceneBuilder&) = delete;
    SceneBuilder& operator=(SceneBuilder&&) = delete;

    [[nodiscard]] SceneBuilder& addNode(std::unique_ptr<Node> node) noexcept {
        if (_scene->nodeCount() == _scene_node_buffer_size)
            DULL_WARN("[SCENE BUILDER] Scene node buffer exceeded");

        _scene->addNode(std::move(node));
        return *this;
    }

    void pushToSystem(GameInfo::SceneID scene_id, bool is_startup_scene = false) noexcept;
};