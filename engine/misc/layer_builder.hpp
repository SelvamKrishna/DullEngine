#pragma once

#include "engine/process/layer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

// =======================
// String hashed owned collection of Data
// =======================
class LayerBuilder {
private:
    std::unique_ptr<process::Layer> _layer;

public:
    static constexpr size_t DEFAULT_CAPACITY { 16 };

    explicit LayerBuilder(std::string layer_name, size_t reserve = DEFAULT_CAPACITY);

    // Directly create and adds node to layer
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

    // Directly create and adds node to layer as active
    template <typename NodeT, typename... Args>
        requires std::is_base_of_v<process::Node, NodeT>
    LayerBuilder& addNode(Args&&... args)
    {
        return addNode<NodeT>(true, std::forward<Args>(args)...);
    }

    [[nodiscard]]
    std::unique_ptr<process::Layer> build() noexcept;

    // Directly pushes `Layer` into the static `LayerBuffer` within `Scene`
    process::Layer::ID pushToBuffer() noexcept;
};

} // namespace dull::misc
