#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/misc/node_handle.hpp"
#include "engine/misc/processor.hpp"
#include "engine/process/node.hpp"

#include <vendor/zlog_v2.hpp>

#include <memory>
#include <algorithm>
#include <functional>
#include <type_traits>

// Forward Declaration
namespace dull::misc { class LayerBuilder; }

namespace dull::process {

struct LayerTag final {};

// =======================
// Collection of all Nodes
// =======================
class Layer : private misc::IProcessor, public misc::Identified<LayerTag> {
    friend core::App;
    friend class Scene;
    friend class misc::LayerNodeHandle;
    friend class misc::LayerBuilder;

private:
    misc::Buffer<Node> _nodes; //< Collection of Nodes

    using NodeIt = misc::Buffer<Node>::iterator;

    void iStart() final;
    void iProcess() final;
    void iFixedProcess() final;

    // Detaches node from layer
    // Used by the NodeHandle
    void _disconnect(Node::ID id) noexcept;

public:
    static constexpr size_t DEFAULT_BUFFER_SIZE { 16 };

    Layer(std::string name, size_t reserve = DEFAULT_BUFFER_SIZE);
    ~Layer() = default;

    constexpr Layer(Layer&&)                 noexcept = delete;
    constexpr Layer(const Layer&)            noexcept = delete;
    constexpr Layer& operator=(Layer&&)      noexcept = delete;
    constexpr Layer& operator=(const Layer&) noexcept = delete;

    [[nodiscard]]
    size_t getNodeCount() const noexcept { return _nodes.size(); }

    void shrinkToFit() noexcept { _nodes.shrinkToFit(); }
    void addNode(std::unique_ptr<Node> node, bool is_active = true) noexcept;
    void removeAllNodes() noexcept;

    // Get the NodeHandle of a Node using its type
    template <typename NodeT>
        requires std::is_base_of_v<Node, NodeT>
    [[nodiscard]]
    misc::LayerNodeHandle getNodeHandle() noexcept
    {
        NodeIt it = std::find_if(
            _nodes.begin(), _nodes.end(),
            [](const std::unique_ptr<Node>& node)
            { return dynamic_cast<const NodeT*>(node.get()) != nullptr; }
        );

        ZASSERT(
            it != _nodes.end(),
            "Unable to find Node '{}' in Layer '{}'",
            typeid(NodeT).name(), getName()
        );

        return misc::LayerNodeHandle { *this, (*it)->getID() };
    }

    // Get the NodeHandle of a Node using its name (UNIQUE within Layer)
    [[nodiscard]]
    misc::LayerNodeHandle getNodeHandle(Node::ID node_id) noexcept;

    // Read only access to all underlying Nodes
    [[nodiscard]]
    misc::Buffer<Node>& getAllNodes() noexcept { return _nodes; }

    // Map a function to all Active Layers
    void forAllNodes(const std::function<void(Node&)>& function) noexcept;
};

} // namespace dull::process
