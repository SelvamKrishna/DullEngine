#include "engine/misc/layer_builder.hpp"
#include "engine/process/scene.hpp"

namespace dull::misc {

LayerBuilder:: LayerBuilder(std::string layer_name, size_t reserve)
: _layer {std::make_unique<process::Layer>(layer_name, reserve)}
{}

[[nodiscard]]
std::unique_ptr<process::Layer> LayerBuilder::build() noexcept
{
    ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
    return std::move(_layer);
}

process::Layer::ID LayerBuilder::pushToBuffer() noexcept
{
    ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);

    process::Layer::ID layer_id = _layer->getID();
    std::string name_copy = std::string{_layer->getName()};

    ZASSERT(
        process::Scene::getLayerBuffer().add(std::move(_layer)),
        "LayerBuffer failed to load Layer '{}'", name_copy
    );

    return layer_id;
}

} // namespace dull::misc
