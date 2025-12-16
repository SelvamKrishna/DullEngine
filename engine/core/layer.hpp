#pragma once

#include "engine/core/node.hpp"
#include "engine/core/node_handle.hpp"

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

namespace dull::core {

class Layer final {
    friend class SceneSystem;
    friend class NodeHandle;

private:
    using NodeIt = std::vector<CtxNodePair>::iterator;

    std::string _name;
    std::vector<CtxNodePair> _nodes;

    void _activate();
    void _process();
    void _fixedProcess();

    static void _disconnect(NodeIt node_it) noexcept;

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
    ) noexcept
    : _name(name) { _nodes.reserve(initial_capacity); }

    ~Layer() = default;

    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }

    [[nodiscard]]
    size_t getNodeCount() const noexcept { return _nodes.size(); }

    void shrinkToFit() noexcept { _nodes.shrink_to_fit(); }

    void addNode(std::string name, std::unique_ptr<Node> node, bool is_active = true) noexcept;
    void removeAllNodes() noexcept;

    template <typename NodeT>
        requires std::is_base_of_v<Node, NodeT>
    [[nodiscard]]
    NodeHandle getNodeHandle() noexcept
    {
        std::vector<CtxNodePair>::iterator it = std::find_if(
            _nodes.begin(), _nodes.end(),
            [](const CtxNodePair& node)
            { return dynamic_cast<const NodeT*>(node.uptr.get()) != nullptr; }
        );

        ZASSERT(
            it != _nodes.end(),
            "Unable to find Node '{}' in Layer '{}'",
            typeid(NodeT).name(), _name
        );

        return NodeHandle { *this, it };
    }

    [[nodiscard]]
    NodeHandle getNodeHandle(std::string_view name) noexcept;

    [[nodiscard]]
    NodeHandle getNodeHandle(size_t index) noexcept;

    void logStats() const noexcept;

#undef _T_NODE

};

} // namespace dull::core
