#pragma once

#include "engine/core/layer_buffer.hpp"

#include <vendor/zutils/test.hpp>

#include <vector>

namespace dull::core {

class Scene final {
private:
    std::vector<std::string_view> _layers;

public:
    explicit Scene() : _layers {} {}
    explicit Scene(std::initializer_list<std::string_view> layers) : _layers {layers} {}

    void addLayer(std::string_view layer_name, size_t idx = UINT64_MAX)
    {
        ZASSERT_S(
            std::find(_layers.begin(), _layers.end(), layer_name) == _layers.end(),
            "Layer with name '" + std::string{layer_name} + "' already exists"
        );

        if (idx == UINT64_MAX)
            _layers.emplace_back(layer_name);
        else
            _layers.insert(_layers.begin() + idx, layer_name);
    }
    void removeLayer(size_t index)
    {
        ZASSERT_S(index < _layers.size(), "Index out of range");
        std::erase(_layers, _layers[index]);
    }
    void removeLayer(std::string_view layer_name)
    {
        std::erase_if(_layers, [&layer_name](const std::string_view& l_name) {
            return l_name == layer_name;
        });
    }

    [[nodiscard]]
    std::vector<std::string_view>& getActiveLayers() noexcept { return _layers; }
};

class SceneSystem final {
    friend class App;

private:
    LayerBuffer _layer_buffer;
    Scene       _current_scene;

    explicit SceneSystem() = default;
    ~SceneSystem() = default;

    void _activate()
    {
        for (auto& layer : _current_scene.getActiveLayers())
            _layer_buffer.getLayer(layer)->_activate();
    }
    void _process()
    {
        for (auto& layer : _current_scene.getActiveLayers())
            _layer_buffer.getLayer(layer)->_process();
    }
    void _fixedProcess()
    {
        for (auto& layer : _current_scene.getActiveLayers())
            _layer_buffer.getLayer(layer)->_fixedProcess();
    }

public:
    void setCurrentScene(Scene new_scene) noexcept { _current_scene = new_scene; }

    [[nodiscard]]
    Scene& getCurrentScene() noexcept { return _current_scene; }

    [[nodiscard]]
    LayerBuffer& getLayerBuffer() noexcept { return _layer_buffer; }

    [[nodiscard]]
    bool isLayerActive(std::string_view layer_name) noexcept
    {
        for (const std::string_view& ACTIVE_LAYER : _current_scene.getActiveLayers())
            if (ACTIVE_LAYER == layer_name) return true;

        return false;
    }
};

} // namespace dull::core
