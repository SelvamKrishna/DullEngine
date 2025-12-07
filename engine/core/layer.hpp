#pragma once

#include "engine/core/node.hpp"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>

namespace dull::core {

class Layer final {
    friend class SceneSystem;

private:
    using NodeIt      = std::vector<std::unique_ptr<Node>>::iterator;
    using NodeConstIt = std::vector<std::unique_ptr<Node>>::const_iterator;

    std::string                        _name;
    std::vector<std::unique_ptr<Node>> _nodes;

    void _activate()
    {
        for (auto& node : _nodes)
            node->_start();
    }
    void _process()
    {
        for (auto& node : _nodes)
            node->_update();
    }
    void _fixedProcess()
    {
        for (auto& node : _nodes)
            node->_fixedUpdate();
    }

    [[nodiscard]]
    Layer::NodeIt _findIterator(std::string_view name) noexcept;

    [[nodiscard]]
    Layer::NodeConstIt _findIterator(std::string_view name) const noexcept;

#define _T_NODE(T) \
    template <typename T> \
        requires std::is_base_of_v<Node, T> \

    _T_NODE(NodeT)
    [[nodiscard]]
    auto _findIterator(this auto& self) noexcept
    {
        return std::find_if(
            self._nodes.begin(), self._nodes.end(),
            [](const std::unique_ptr<Node>& node) {
                return dynamic_cast<NodeT*>(node.get()) != nullptr;
            }
        );
    }

public:
    static constexpr size_t DEFAULT_CAPACITY = 16;

    Layer() = delete;

    Layer(Layer&&)                 = delete;
    Layer(const Layer&)            = delete;
    Layer& operator=(Layer&&)      = delete;
    Layer& operator=(const Layer&) = delete;

    explicit Layer(
        std::string_view name,
        size_t initial_capacity = DEFAULT_CAPACITY
    ) noexcept : _name{name}
    {
        _nodes.reserve(initial_capacity);
        /// TODO: push layer into layer buffer
    }

    ~Layer() = default;

    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }

    [[nodiscard]]
    constexpr size_t getNodeCount() const noexcept { return _nodes.size(); }

    constexpr void shrinkToFit() noexcept { _nodes.shrink_to_fit(); }

    void addNode(std::unique_ptr<Node> node) noexcept;
    void removeNode(std::string_view name) noexcept;
    void removeAllNodes() noexcept;

    [[nodiscard]]
    Node* findNode(this auto& self, std::string_view name) noexcept;

    [[nodiscard]]
    bool hasNode(std::string_view name) const noexcept { return findNode(name) != nullptr; }

    [[nodiscard]]
    Node& getNode(std::string_view name) const;

    [[nodiscard]]
    Node* tryGetNode(std::string_view name) const noexcept;

    [[nodiscard]]
    Node* getNodeByIndex(this auto& self, size_t index) noexcept;

    [[nodiscard]]
    std::unique_ptr<Node> extractNode(std::string_view name) noexcept;

    template <typename NodeT, typename... Args>
        requires std::is_base_of_v<Node, NodeT>
    void createNode(std::string_view name, Args &&...args) noexcept
    {
        _nodes.emplace_back(std::make_unique<NodeT>(name, std::forward<Args>(args)...));
    }

    _T_NODE(NodeT)
    void removeNode() noexcept
    {
        std::erase_if(
            _nodes,
            [](const auto& node) { return dynamic_cast<NodeT*>(node.get()) != nullptr; }
        );
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    NodeT* findNode(this auto& self) noexcept
    {
        auto it = self.template _findIterator<NodeT>();
        return it != self._nodes.end() ? static_cast<NodeT*>(it->get()) : nullptr;
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    bool hasNode() const noexcept { return findNode<NodeT>() != nullptr; }

    _T_NODE(NodeT)
    [[nodiscard]]
    NodeT& getNode() const noexcept
    {
        auto* node = findNode<NodeT>();
        ZASSERT_NE(node, nullptr);
        return *node;
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    Node* tryGetNode() const noexcept { return const_cast<Node*>(this->findNode<NodeT>()); }

    _T_NODE(NodeT)
    [[nodiscard]]
    std::unique_ptr<NodeT> extractNode() noexcept
    {
        auto it = _findIterator<NodeT>();
        std::unique_ptr<Node> node {};

        if (it != _nodes.end()) {
            node = std::move(*it);
            _nodes.erase(it);
        }

        return node;
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    std::vector<NodeT*> getAllNodesOfType() const
    {
        std::vector<NodeT*> result;

        for (const auto& NODE : _nodes)
        {
            NodeT* casted = dynamic_cast<NodeT*>(NODE.get());
            if (casted) result.push_back(casted);
        }

        result.shrink_to_fit();
        return result;
    }

#undef _T_NODE

    void logStats() const noexcept;
};

} // namespace dull::core
