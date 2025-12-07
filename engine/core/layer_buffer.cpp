#include "engine/core/layer_buffer.hpp"

#include <vendor/zutils/test.hpp>

namespace dull::core {

void LayerBuffer::loadLayer(const std::string& name, std::shared_ptr<Layer> layer)
{
    _layers[name] = std::move(layer);
}

[[nodiscard]]
std::shared_ptr<Layer> LayerBuffer::getLayer(const std::string& name) const
{
    auto it = _layers.find(name);
    ZEXPECT_S(it != _layers.end(), "Cant find layer '" + name + "' in LayerBuffer");
    return it != _layers.end() ? it->second : nullptr;
}

} // namespace dull::core
