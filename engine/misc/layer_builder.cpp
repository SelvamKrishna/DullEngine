#include "engine/misc/layer_builder.hpp"
#include "engine/misc/buffer.hpp"
#include "engine/process/scene.hpp"

namespace dull::misc {

LayerBuilder::LayerBuilder(std::string layer_name)
: _layer {std::make_unique<process::Layer>(layer_name)}
{}

LayerBuilder& LayerBuilder::reserve(size_t capacity) noexcept
{
    _layer->_nodes.reserve(capacity);
    return *this;
}

[[nodiscard]]
std::unique_ptr<process::Layer> LayerBuilder::build() noexcept
{
    ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
    return std::move(_layer);
}

void LayerBuilder::pushToBuffer() noexcept
{
    ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
    process::Scene::getLayerBuffer().loadData(_layer->getName(), std::move(_layer));
}

} // namespace dull::misc
