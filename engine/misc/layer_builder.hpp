#pragma once

#include "engine/process/layer.hpp"
#include "engine/process/scene.hpp"
#include "engine/misc/buffer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

class LayerBuilder {
private:
    std::unique_ptr<process::Layer> _layer;

public:
    explicit LayerBuilder(std::string layer_name)
    : _layer {std::make_unique<process::Layer>(std::move(layer_name))}
    {}

    LayerBuilder& reserve(size_t capacity) noexcept
    {
        _layer->_nodes.reserve(capacity);
        return *this;
    }

    template <typename NodeT, typename... Args>
        requires std::is_base_of_v<process::Node, NodeT>
    LayerBuilder& addNode(bool is_active, Args&&... args)
    {
        _layer->addNode(
            std::make_unique<NodeT>(std::forward<Args>(args)...),
            is_active
        );

        return *this;
    }

    template <typename NodeT, typename... Args>
        requires std::is_base_of_v<process::Node, NodeT>
    LayerBuilder& addNode(Args&&... args)
    {
        return addNode<NodeT>(true, std::forward<Args>(args)...);
    }

    [[nodiscard]]
    std::unique_ptr<process::Layer> build() noexcept
    {
        ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
        return std::move(_layer);
    }

    void pushToBuffer() noexcept
    {
        ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
        process::Scene::getLayerBuffer().loadData(_layer->getName(), std::move(_layer));
    }
};

} // namespace dull::misc
