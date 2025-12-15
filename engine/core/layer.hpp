#pragma once

#include "engine/core/node.hpp"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

namespace dull::core {

class Layer final {
    friend class SceneSystem;

private:
    struct CtxNodePair final {
        std::string           name;
        std::unique_ptr<Node> uptr;
    };

    using NodeIt      = std::vector<CtxNodePair>::iterator;
    using NodeConstIt = std::vector<CtxNodePair>::const_iterator;

    std::string _name;
    std::vector<CtxNodePair> _nodes;

    void _activate();
    void _process();
    void _fixedProcess();

    [[nodiscard]]
    NodeIt _findIterator(std::string_view name) noexcept;

    [[nodiscard]]
    NodeConstIt _findIterator(std::string_view name) const noexcept;

#define _T_NODE(T) \
    template <typename T> \
        requires std::is_base_of_v<Node, T>

    _T_NODE(NodeT)
    [[nodiscard]]
    NodeIt _findIterator() noexcept
    {
        return std::find_if(
            _nodes.begin(), _nodes.end(),
            [](const CtxNodePair& p) {
                return dynamic_cast<NodeT*>(p.uptr.get()) != nullptr;
            }
        );
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    NodeConstIt _findIterator() const noexcept
    {
        return std::find_if(
            _nodes.begin(), _nodes.end(),
            [](const CtxNodePair& p) {
                return dynamic_cast<const NodeT*>(p.uptr.get()) != nullptr;
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

    explicit Layer(std::string_view name,
                   size_t initial_capacity = DEFAULT_CAPACITY) noexcept
        : _name(name)
    {
        _nodes.reserve(initial_capacity);
    }

    ~Layer() = default;

    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }

    [[nodiscard]]
    size_t getNodeCount() const noexcept { return _nodes.size(); }

    void shrinkToFit() noexcept { _nodes.shrink_to_fit(); }

    void addNode(std::string name, std::unique_ptr<Node> node, bool is_active = true) noexcept;
    void removeNode(std::string_view name) noexcept;
    void removeAllNodes() noexcept;

    [[nodiscard]]
    Node* findNode(std::string_view name) noexcept;

    [[nodiscard]]
    const Node* findNode(std::string_view name) const noexcept;

    [[nodiscard]]
    bool hasNode(std::string_view name) const noexcept { return findNode(name) != nullptr; }

    [[nodiscard]]
    const Node& getNode(std::string_view name) const;

    [[nodiscard]]
    Node& getNode(std::string_view name);

    [[nodiscard]]
    Node* tryGetNode(std::string_view name) const noexcept;

    [[nodiscard]]
    Node* getNodeByIndex(this auto& self, size_t index) noexcept;

    [[nodiscard]]
    std::unique_ptr<Node> extractNode(std::string_view name) noexcept;

    template <typename NodeT, typename... Args>
        requires std::is_base_of_v<Node, NodeT>
    void createNode(std::string_view name, Args&&... args) noexcept
    {
        _nodes.push_back({
            std::string{name},
            std::make_unique<NodeT>(name, std::forward<Args>(args)...)
        });
    }

    _T_NODE(NodeT)
    void removeNode() noexcept
    {
        std::erase_if(_nodes, [](const CtxNodePair& p) {
            return dynamic_cast<NodeT*>(p.uptr.get()) != nullptr;
        });
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    NodeT* findNode() noexcept
    {
        auto it = _findIterator<NodeT>();
        return it != _nodes.end()
                 ? static_cast<NodeT*>(it->uptr.get())
                 : nullptr;
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    bool hasNode() const noexcept
    {
        return findNode<NodeT>() != nullptr;
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    NodeT& getNode() noexcept
    {
        auto* node = findNode<NodeT>();
        ZASSERT(node != nullptr);
        return *node;
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    std::unique_ptr<NodeT> extractNode() noexcept
    {
        auto it = _findIterator<NodeT>();
        if (it == _nodes.end())
            return {};

        auto base = std::move(it->uptr);
        _nodes.erase(it);
        return std::unique_ptr<NodeT>(static_cast<NodeT*>(base.release()));
    }

    _T_NODE(NodeT)
    [[nodiscard]]
    std::vector<NodeT*> getAllNodesOfType() const
    {
        std::vector<NodeT*> result;

        for (const auto& p : _nodes) {
            if (auto* casted = dynamic_cast<NodeT*>(p.uptr.get()))
                result.push_back(casted);
        }

        return result;
    }

#undef _T_NODE

    void logStats() const noexcept;
};

} // namespace dull::core
