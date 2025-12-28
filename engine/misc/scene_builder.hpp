#pragma once

#include "engine/process/scene.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

struct SceneBuilderContext {
    std::string scene_name;
    std::initializer_list<process::Scene::LayerConfig> layers;
};

// =======================
// Builder patter for Scene
// =======================
class SceneBuilder {
private:
    std::unique_ptr<process::Scene> _scene;

public:
    static constexpr size_t DEFAULT_CAPACITY { 16 };

    explicit SceneBuilder(std::string scene_name, size_t reserve = DEFAULT_CAPACITY);

    // Adds `Layer` to `Scene`
    SceneBuilder& addLayer(std::string_view layer_name, bool active = true, size_t idx = UINT64_MAX);

    // Adds multiple `Layer` to `Scene` in the provided order
    SceneBuilder& addLayers(std::initializer_list<process::Scene::LayerConfig> layers);

    [[nodiscard]]
    std::unique_ptr<process::Scene> build() noexcept;

    // Directly pushes `Scene` into the static `SceneBuffer` within `World`
    void pushToBuffer() noexcept;
};

} // namespace dull::misc
