#include "engine/core/scene.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

void Scene::addLayer(std::string_view layer_name, size_t idx, bool active)
{
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_name](const auto& layer) { return layer.first == layer_name; }
    );

    ZASSERT(
        it == _layers.end(),
        "Layer with name '" + std::string{layer_name} + "' already exists"
    );

    if (idx == UINT64_MAX)
        _layers.emplace_back(layer_name, active);
    else
        _layers.insert(_layers.begin() + idx, std::make_pair(layer_name, active));
}

void Scene::removeLayer(size_t index)
{
    ZASSERT(index < _layers.size(), "Index out of range");
    std::erase(_layers, _layers[index]);
}

void Scene::removeLayer(std::string_view layer_name)
{
    std::erase_if(
        _layers,
        [&layer_name](const auto& layer) { return layer.first == layer_name; }
    );
}

[[nodiscard]]
LayerGroup Scene::getLayersBy(
    std::function<bool(const LayerContext&)> condition
) noexcept {
    if (_layers.empty()) [[unlikely]] return {};

    LayerGroup layer_group;
    layer_group.reserve(_layers.size());

    for (const auto& LAYER : _layers) if (condition(LAYER)) {
        layer_group.emplace_back(LAYER.first);
    }

    layer_group.shrink_to_fit();
    return layer_group;
}

[[nodiscard]]
LayerGroup Scene::getActiveLayers() noexcept
{
    return getLayersBy([](const LayerContext& layer){ return layer.second; });
}

[[nodiscard]]
LayerGroup Scene::getInactiveLayers() noexcept
{
    return getLayersBy([](const LayerContext& layer){ return !layer.second; });
}

[[nodiscard]]
bool Scene::isLayerActive(std::string_view layer_name) noexcept
{
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_name](const auto& layer) { return layer.first == layer_name; }
    );

    return it != _layers.end() || it->second;
}

void Scene::setLayerActive(std::string_view layer_name, bool active) noexcept
{
    auto it = std::find_if(
        _layers.begin(), _layers.end(),
        [&layer_name](const LayerContext& LAYER) { return LAYER.first == layer_name; }
    );

    ZASSERT(
        it != _layers.end(),
        "Layer (" + std::string{layer_name} + ") Not found"
    );

    if (it->second == active) return;

    it->second = active;
    ZUNIMPLEMENTED("Newly set active layer not yet activated");
}

} // namespace dull::core
