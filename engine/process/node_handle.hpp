#pragma once

#include "engine/process/node.hpp"

#include <vector>
#include <memory>

namespace dull::process {

// Forward Declaration
class Layer;

// =======================
// Wrapper for Node to provide Layer related logic
// =======================
class LayerNodeHandle final {
    friend Layer;

private:
    using NodeIt = std::vector<std::unique_ptr<Node>>::iterator;

    Layer& _layer;   //< Reference to Layer owning this Node
    NodeIt _node_it; //< Node location in Layer

    explicit LayerNodeHandle(
        Layer& layer,
        NodeIt node_it
    ) noexcept
    : _layer   {layer}
    , _node_it {node_it}
    {}

public:
    [[nodiscard]]
    Node& getNode() noexcept { return *_node_it->get(); }

    // Removes Node from Layer
    void removeFromLayer() noexcept;

    // Removes Node from Layer and returns it
    [[nodiscard]]
    std::unique_ptr<Node> extractFromLayer() noexcept;
};

} // namespace dull::process
