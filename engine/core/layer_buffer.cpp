#include "engine/config.hpp"
#include "engine/core/layer_buffer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void LayerBuffer::loadLayer(std::unique_ptr<Layer> layer)
{
    std::string_view layer_name = layer->getName();
    ZASSERT(
        _layers.find(layer_name) == _layers.end(),
        "Layer '{}' already exists in LayerBuffer", layer->getName()
    );

    _layers[layer->getName()] = std::move(layer);
    _IF_LOG ZINFO("Layer '{}' loaded to LayerBuffer", layer_name);
}

[[nodiscard]]
std::unique_ptr<Layer>& LayerBuffer::getLayer(std::string_view layer_name) noexcept
{
    auto it = _layers.find(layer_name);
    ZASSERT(
        it != _layers.end(),
        "Layer '{}' not found in LayerBuffer", layer_name
    );

    return it->second;
}

void LayerBuffer::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging LayerBuffer");
    for (const auto& LAYER : _layers) LAYER.second->logStats();
}

#undef _IF_LOG

} // namespace dull::core
