#include "engine/process/scene.hpp"
#include "engine/config.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::process {

misc::Buffer<Layer> Scene::s_layer_buf = {};

Scene::Scene(std::string name, size_t reserve) : misc::Identified<SceneTag> {std::move(name)}
{
    _layers.reserve(reserve);
}

#define _FOR_ALL_ACTIVE_LAYERS(LAYER_VAR, LAYER_OPR) do {    \
    forAllActiveLayers([](Layer& LAYER_VAR) { LAYER_OPR; }); \
} while (0)

void Scene::iStart()        { _FOR_ALL_ACTIVE_LAYERS(layer, layer.iStart()); }
void Scene::iProcess()      { _FOR_ALL_ACTIVE_LAYERS(layer, layer.iProcess()); }
void Scene::iFixedProcess() { _FOR_ALL_ACTIVE_LAYERS(layer, layer.iFixedProcess()); }

#undef _FOR_ALL_ACTIVE_LAYERS

[[nodiscard]]
Scene::LayerIt Scene::_searchLayer(Layer::ID layer_id) noexcept
{
    return std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_id](const LayerConfig& layer_cfg) { return layer_cfg.layer_id == layer_id; }
    );
}

[[nodiscard]]
Scene::LayerConstIt Scene::_searchLayer(Layer::ID layer_id) const noexcept
{
    return std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_id](const LayerConfig& layer_cfg) { return layer_cfg.layer_id == layer_id; }
    );
}

[[nodiscard]]
std::string_view Scene::_getLayerName(Layer::ID layer_id) const noexcept
{
    return s_layer_buf.find(layer_id)->getName();
}

void Scene::addLayer(Layer::ID layer_id, bool active, std::optional<size_t> idx)
{
    ZASSERT(
        _searchLayer(layer_id) == _layers.end(),
        "Layer '{}' already exists in Scene '{}'",
        _getLayerName(layer_id), getName()
    );

    ZON_DEBUG {
        if (_layers.size() == _layers.capacity()) [[unlikely]]
            ZPERFORMANCE("Scene '{}' size exceeding capacity of '{}'", getName(), _layers.size());
    }

    idx
    ? (void)_layers.emplace(_layers.begin() + *idx, layer_id, active)
    : (void)_layers.emplace_back(layer_id, active);

    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Layer '{}' added to Scene '{}'",
        _getLayerName(layer_id), getName()
    );
}

void Scene::removeLayer(Layer::ID layer_id)
{
    std::erase_if(
        _layers,
        [&layer_id](const LayerConfig& layer) { return layer.layer_id == layer_id; }
    );

    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Layer '{}' removed to Scene '{}'",
        _getLayerName(layer_id), getName()
    );
}

[[nodiscard]]
Scene::LayerGroup Scene::getLayersBy(std::function<bool(const LayerConfig&)> condition) noexcept
{
    if (_layers.empty()) [[unlikely]] return {};

    LayerGroup layer_group;
    layer_group.reserve(_layers.size());

    for (const auto& LAYER : _layers) if (condition(LAYER))
        layer_group.emplace_back(LAYER.layer_id);

    layer_group.shrink_to_fit();
    return layer_group;
}

[[nodiscard]]
Scene::LayerGroup Scene::getActiveLayers() noexcept
{
    return getLayersBy([](const LayerConfig& layer){ return layer.is_active; });
}

[[nodiscard]]
Scene::LayerGroup Scene::getInactiveLayers() noexcept
{
    return getLayersBy([](const LayerConfig& layer){ return !layer.is_active; });
}

void Scene::forAllActiveLayers(LayerMethod& function) noexcept
{
    for (const auto& [ID, IS_ACTIVE] : _layers) if (IS_ACTIVE)
        function(*s_layer_buf.find(ID));
}

[[nodiscard]]
bool Scene::isLayerActive(Layer::ID layer_id) noexcept
{
    LayerConstIt it = _searchLayer(layer_id);
    return it != _layers.end() || it->is_active;
}

void Scene::setLayerActive(Layer::ID layer_id, bool active) noexcept
{
    LayerIt it = _searchLayer(layer_id);

    ZASSERT(
        it != _layers.end(),
        "Layer '{}' Not found in Scene", _getLayerName(layer_id)
    );

    if (it->is_active == active) return; // No changes
    it->is_active = active;

    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Layer '{}' made {} in Scene '{}'",
        _getLayerName(layer_id), active ? "active" : "inactive", getName()
    );
}

} // namespace dull::process
