#pragma once

#include "engine/process/node.hpp"

#include <vector>
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
    using NodeIt = std::vector<std::unique_ptr<process::Node>>::iterator;

    process::Layer& _layer; //< Reference to Layer owning this Node
    NodeIt _node_it;        //< Node location in Layer

    explicit LayerNodeHandle(process::Layer& layer, NodeIt node_it) noexcept
    : _layer   {layer}
    , _node_it {node_it}
    {}

public:
    [[nodiscard]]
    process::Node& getNode() noexcept { return *_node_it->get(); }

    // Removes Node from Layer
    void removeFromLayer() noexcept;

    // Removes Node from Layer and returns it
    [[nodiscard]]
    std::unique_ptr<process::Node> extractFromLayer() noexcept;
};

} // namespace dull::misc
