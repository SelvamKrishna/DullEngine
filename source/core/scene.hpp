#pragma once

#include <algorithm>
#include <cstddef>
#include <memory>
#include <string_view>
#include <type_traits>
#include <vector>

#include "../utils/debug.hpp"
#include "node.hpp"

/// TODO: Better Scene management system
class Scene {
    friend class App;

private:
    static constexpr size_t DEFAULT_NODE_BUFFER_SIZE = 16;
    std::vector<std::shared_ptr<Node>> _nodes;

    void _init();
    void _update();
    void _fixedUpdate();

public:
    constexpr explicit Scene(size_t node_buffer_size = DEFAULT_NODE_BUFFER_SIZE) noexcept {
        _nodes.reserve(node_buffer_size);
    }

    ~Scene() noexcept { clear(); }

    Scene(const Scene &) = delete;
    Scene(Scene &&) = default;
    Scene &operator=(const Scene &) = delete;
    Scene &operator=(Scene &&) = default;

    void addNode(std::unique_ptr<Node> node);

    void removeNodeByIndex(size_t index);
    void removeNodeByName(std::string_view name);

    template <typename NodeT>
        requires std::is_base_of_v<Node, NodeT>
    void removeNode() {
        auto it = std::ranges::find_if(_nodes, [](const auto &node) {
            return dynamic_cast<NodeT *>(node.get()) != nullptr;
        });

        if (it == _nodes.end()) {
            ErrorCtx("Remove node by type")
                .failFallback(std::format("Type <{}> Not found", typeid(NodeT).name()));
            return;
        }

        _nodes.erase(it);
    }

    void clear() { _nodes.clear(); }

    [[nodiscard]] size_t nodeCount() const noexcept { return _nodes.size(); }

    [[nodiscard]] std::weak_ptr<Node> getNodeByIndex(size_t index);
    [[nodiscard]] std::weak_ptr<Node> getNodeByName(std::string_view name);

    template <typename NodeT>
        requires std::is_base_of_v<Node, NodeT>
    [[nodiscard]] std::weak_ptr<NodeT> getNode() {
        auto it = std::ranges::find_if(_nodes, [](const auto &node) {
            return dynamic_cast<NodeT *>(node.get()) != nullptr;
        });

        if (it == _nodes.end()) {
            ErrorCtx("Get node by type")
                .failFallback(std::format("Type <{}> Not found", typeid(NodeT).name()));
            return {};
        }

        return std::static_pointer_cast<NodeT>(*it);
    }
};