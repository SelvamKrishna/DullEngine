#pragma once

#include "engine/process/layer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

class LayerBuilder {
private:
    std::unique_ptr<process::Layer> _layer;

public:
    explicit LayerBuilder(std::string layer_name);

    LayerBuilder& reserve(size_t capacity) noexcept;

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
    std::unique_ptr<process::Layer> build() noexcept;

    void pushToBuffer() noexcept;
};

} // namespace dull::misc
