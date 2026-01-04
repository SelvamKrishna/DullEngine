#include "engine/config.hpp"
#include "engine/process/scene.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::process {

misc::Buffer<Layer> Scene::s_layer_buf = {};

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

Scene::Scene(std::string name, size_t reserve) : misc::Identified<SceneTag> {std::move(name)}
{
    _layers.reserve(reserve);
}

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

void Scene::addLayer(Layer::ID layer_id, bool active, std::optional<size_t> idx)
{
    ZASSERT(
        std::find_if(
            _layers.begin(), _layers.end(),
            [&layer_id](const LayerConfig& scene_layer)
            { return scene_layer.layer_id == layer_id; }
        ) == _layers.end(),
        "Layer '{}' already exists in Scene '{}'",
        s_layer_buf.find(layer_id)->getName(), getName()
    );

    ZON_DEBUG {
        if (_layers.size() == _layers.capacity()) [[unlikely]]
            ZPERFORMANCE("Scene '{}' size exceeding capacity of '{}'", getName(), _layers.size());
    }

    if (!idx) // Default
        _layers.emplace_back(layer_id, active);
    else
        _layers.emplace(_layers.begin() + *idx, layer_id, active);

    _IF_LOG ZINFO(
        "Layer '{}' added to Scene '{}'",
        s_layer_buf.find(layer_id)->getName(), getName()
    );
}

void Scene::removeLayer(Layer::ID layer_id)
{
    std::erase_if(
        _layers,
        [&layer_id](const LayerConfig& layer) { return layer.layer_id == layer_id; }
    );

    _IF_LOG ZINFO(
        "Layer '{}' removed to Scene '{}'",
        s_layer_buf.find(layer_id)->getName(), getName()
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
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_id](const auto& layer) { return layer.layer_id == layer_id; }
    );

    return it != _layers.end() || it->is_active;
}

void Scene::setLayerActive(Layer::ID layer_id, bool active) noexcept
{
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_id](const LayerConfig& LAYER) { return LAYER.layer_id == layer_id; }
    );

    ZASSERT(
        it != _layers.end(),
        "Layer '{}' Not found in Scene", s_layer_buf.find(layer_id)->getName()
    );

    if (it->is_active == active) return; // No changes
    it->is_active = active;

    _IF_LOG ZINFO(
        "Layer '{}' made {} in Scene '{}'",
        s_layer_buf.find(layer_id)->getName(), active ? "active" : "inactive", getName()
    );
}

#undef _IF_LOG

} // namespace dull::process
