#pragma once

#include "engine/process/node.hpp"

#include <memory>

// Forward Declaration
namespace dull::process { class Layer; }

namespace dull::misc {

// =======================
// Wrapper for Node to provide Layer related logic
// =======================
class LayerNodeHandle final {
    friend process::Layer;

private:
    process::Layer&   _layer;   //< Reference to Layer owning this Node
    process::Node::ID _node_id; //< Node ID

    explicit LayerNodeHandle(process::Layer& layer, process::Node::ID id) noexcept
    : _layer   {layer}
    , _node_id {id}
    {}

    // Get Node pointer from Layer's buffer
    [[nodiscard]] process::Node* findNode() noexcept;

public:
    // Get underlying Node from Layer's buffer
    [[nodiscard]] process::Node& getNode() noexcept;

    // Removes Node from Layer
    void removeFromLayer() noexcept;

    // Removes Node from Layer and returns it
    [[nodiscard]] std::unique_ptr<process::Node> extractFromLayer() noexcept;
};

} // namespace dull::misc
