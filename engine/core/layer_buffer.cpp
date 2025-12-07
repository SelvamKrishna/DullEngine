#include "engine/core/layer_buffer.hpp"

#include <vendor/zutils/test.hpp>

namespace dull::core {

void LayerBuffer::loadLayer(std::unique_ptr<Layer> layer)
{
    ZASSERT_S(
        _layers.find(layer->getName()) == _layers.end(),
        "Layer with name " + std::string{layer->getName()} + " already exists in LayerBuffer"
    );

    _layers[std::string{layer->getName()}] = std::move(layer);
}

} // namespace dull::core
