#pragma once

#include "engine/process/node.hpp"

#include <vector>
#include <string>
#include <memory>
#include <string_view>

namespace dull::process {

// Forward Declaration
class Layer;

// =======================
// NodeName : NodePointer
// =======================
struct NodeCtx final {
    std::string           name; //< Node name (UNIQUE within Layer)
    std::unique_ptr<Node> uptr; //< Pointer to Node
};

// =======================
// Wrapper for Node to provide Layer related logic
// =======================
class NodeHandle final {
    friend Layer;

private:
    Layer& _layer; //< Reference to Layer owning this Node
    std::vector<NodeCtx>::iterator _node_it; //< Node location in Layer

    explicit NodeHandle(
        Layer& layer,
        std::vector<NodeCtx>::iterator node_it
    ) noexcept
    : _layer {layer}
    , _node_it {node_it}
    {}

public:
    NodeHandle() = delete;

    [[nodiscard]]
    const std::string_view getName() const noexcept;

    [[nodiscard]]
    std::unique_ptr<Node>& getNode() noexcept;

    // Removes Node from Layer
    void removeFromLayer() noexcept;

    // Removes Node from Layer and returns it
    [[nodiscard]]
    std::unique_ptr<Node> extractFromLayer() noexcept;
};

} // namespace dull::process
