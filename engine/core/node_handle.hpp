#pragma once

#include "engine/core/node.hpp"

#include <vector>
#include <string>
#include <memory>
#include <string_view>

namespace dull::core {

class Layer;

struct CtxNodePair final {
    std::string           name;
    std::unique_ptr<Node> uptr;
};

class NodeHandle final {
    friend Layer;

private:
    Layer& _layer;
    std::vector<CtxNodePair>::iterator _node_it;

    explicit NodeHandle(
        Layer& layer,
        std::vector<CtxNodePair>::iterator node_it
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

    void removeFromLayer() noexcept;

    [[nodiscard]]
    std::unique_ptr<Node> extractFromLayer() noexcept;
};

} // namespace dull::core
