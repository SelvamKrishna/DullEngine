#include "engine/misc/layer_builder.hpp"
#include "engine/misc/buffer.hpp"
#include "engine/process/scene.hpp"

namespace dull::misc {

LayerBuilder:: LayerBuilder(std::string layer_name, size_t reserve)
: _layer {std::make_unique<process::Layer>(layer_name)}
{
    _layer->_nodes.reserve(reserve);
}

[[nodiscard]]
std::unique_ptr<process::Layer> LayerBuilder::build() noexcept
{
    ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
    return std::move(_layer);
}

void LayerBuilder::pushToBuffer() noexcept
{
    std::string name_copy = std::string{_layer->getName()};

    ZASSERT(_layer != nullptr, "LayerBuilder::{} called more than once", __func__);
    ZASSERT(
        process::Scene::getLayerBuffer().loadData(_layer->getName(), std::move(_layer)),
        "LayerBuffer failed to load Layer '{}'", name_copy
    );
}

} // namespace dull::misc
