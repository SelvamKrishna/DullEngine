#include "engine/config.hpp"
#include "engine/process/scene.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::process {

misc::Buffer<Layer> Scene::s_layer_buf = {};

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void Scene::iStart()
{
    forAllActiveLayers([](Layer& layer) { layer.iStart(); });
}

void Scene::iProcess()
{
    forAllActiveLayers([](Layer& layer) { layer.iProcess(); });
}

void Scene::iFixedProcess()
{
    forAllActiveLayers([](Layer& layer) { layer.iFixedProcess(); });
}

void Scene::addLayer(std::string_view layer_name, size_t idx, bool active)
{
    if (idx == UINT64_MAX) // Default
        _layers.emplace_back(layer_name, active);
    else
        _layers.insert(_layers.begin() + idx, { layer_name, active });

    _IF_LOG ZINFO("Layer '{}' added to Scene", layer_name);
}

void Scene::removeLayer(std::string_view layer_name)
{
    std::erase_if(
        _layers,
        [&layer_name](const auto& layer) { return layer.layer_name == layer_name; }
    );

    _IF_LOG ZINFO("Layer '{}' removed to Scene", layer_name);
}

[[nodiscard]]
LayerGroup Scene::getLayersBy(std::function<bool(const LayerConfig&)> condition) noexcept
{
    if (_layers.empty()) [[unlikely]] return {};

    LayerGroup layer_group;
    layer_group.reserve(_layers.size());

    for (const auto& LAYER : _layers) if (condition(LAYER)) {
        layer_group.emplace_back(LAYER.layer_name);
    }

    layer_group.shrink_to_fit();
    return layer_group;
}

[[nodiscard]]
LayerGroup Scene::getActiveLayers() noexcept
{
    return getLayersBy([](const LayerConfig& layer){ return layer.is_active; });
}

[[nodiscard]]
LayerGroup Scene::getInactiveLayers() noexcept
{
    return getLayersBy([](const LayerConfig& layer){ return !layer.is_active; });
}

void Scene::forAllActiveLayers(LayerMethod& function) noexcept
{
    for (const auto& [NAME, IS_ACTIVE] : _layers) if (IS_ACTIVE)
        function(s_layer_buf.getData(NAME));
}

[[nodiscard]]
bool Scene::isLayerActive(std::string_view layer_name) noexcept
{
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_name](const auto& layer) { return layer.layer_name == layer_name; }
    );

    return it != _layers.end() || it->is_active;
}

void Scene::setLayerActive(std::string_view layer_name, bool active) noexcept
{
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_name](const LayerConfig& LAYER) { return LAYER.layer_name == layer_name; }
    );

    ZASSERT(
        it != _layers.end(),
        "Layer '{}' Not found in Scene", layer_name
    );

    if (it->is_active == active) return; // No changes

    it->is_active = active;
    _IF_LOG ZINFO("Layer '{}' made {}", layer_name, active ? "active" : "inactive");
}

void Scene::logStats() const noexcept
{
    ZON_RELEASE return;

    for (const LayerConfig& LAYER_CTX : _layers)
    {
        ZDBG(
            "{}Layer '{}'{}{}",
            zlog::config::TAB_TAG,
            LAYER_CTX.layer_name,
            zlog::config::TAG_TAG,
            LAYER_CTX.is_active
        );
    }
}

#undef _IF_LOG

} // namespace dull::process
