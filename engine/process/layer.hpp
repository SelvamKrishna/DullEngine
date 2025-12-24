#pragma once

#include "engine/process/node.hpp"
#include "engine/process/node_handle.hpp"
#include "engine/misc/processor.hpp"

#include <vendor/zlog_v2.hpp>

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <functional>
#include <type_traits>

namespace dull::process {

// =======================
// Collection of all Nodes
// =======================
class Layer : private misc::IProcessor {
    friend core::App;
    friend class Scene;
    friend class LayerNodeHandle;

private:
    std::string                        _name;  //< Name of the layer (UNIQUE)
    std::vector<std::unique_ptr<Node>> _nodes; //< Collection of Nodes

    using NodeIt = std::vector<std::unique_ptr<Node>>::iterator;

    void iStart() final;
    void iProcess() final;
    void iFixedProcess() final;

    // Detaches node from layer
    // Used by the NodeHandle
    void _disconnect(NodeIt node_it) noexcept;

public:
    static constexpr size_t DEFAULT_CAPACITY = 16;

    Layer(Layer&&)                 = delete;
    Layer(const Layer&)            = delete;
    Layer& operator=(Layer&&)      = delete;
    Layer& operator=(const Layer&) = delete;

    explicit Layer(
        std::string name,
        size_t initial_capacity = DEFAULT_CAPACITY
    ) noexcept
    : _name {std::move(name)} { _nodes.reserve(initial_capacity); }

    ~Layer() = default;

    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }

    [[nodiscard]]
    size_t getNodeCount() const noexcept { return _nodes.size(); }

    void shrinkToFit() noexcept { _nodes.shrink_to_fit(); }

    // Adds a node into the Layer
    void addNode(std::unique_ptr<Node> node, bool is_active = true) noexcept;

    // Clears all nodes from Layer
    void removeAllNodes() noexcept;

    // Get the NodeHandle of a Node using its type
    template <typename NodeT>
        requires std::is_base_of_v<Node, NodeT>
    [[nodiscard]]
    LayerNodeHandle getNodeHandle() noexcept
    {
        NodeIt it = std::find_if(
            _nodes.begin(), _nodes.end(),
            [](const std::unique_ptr<Node>& node)
            { return dynamic_cast<const NodeT*>(node.get()) != nullptr; }
        );

        ZASSERT(
            it != _nodes.end(),
            "Unable to find Node '{}' in Layer '{}'",
            typeid(NodeT).name(), _name
        );

        return LayerNodeHandle { *this, it };
    }

    // Get the NodeHandle of a Node using its name (UNIQUE within Layer)
    [[nodiscard]]
    LayerNodeHandle getNodeHandle(std::string_view name) noexcept;

    // Get the NodeHandle of a Node using its index
    [[nodiscard]]
    LayerNodeHandle getNodeHandle(size_t index) noexcept;

    // Read only access to all underlying Nodes
    [[nodiscard]]
    const std::vector<std::unique_ptr<Node>>& getAllNodes() const noexcept { return _nodes; }

    // Map a function to all Active Layers
    void forAllNodes(const std::function<void(Node&)>& function) noexcept;

    // DEV: Logs name and activity of all underlying nodes
    void logStats() const noexcept;
};

} // namespace dull::process
