#pragma once

#include "engine/core/layer_buffer.hpp"
#include "engine/core/scene_buffer.hpp"

#include <string_view>

namespace dull::core {

// =======================
// Manager of all scene related logic
// =======================
class SceneSystem final {
    friend class App;

private:
    LayerBuffer _layer_buffer; //< Collection of all loaded Layers
    SceneBuffer _scene_buffer; //< Collection of all loaded Scenes

    std::string_view _current_scene; //< Scene currently active

    explicit SceneSystem() = default;
    ~SceneSystem() = default;

    void _activate();
    void _process();
    void _fixedProcess();

public:
    [[nodiscard]]
    LayerBuffer& getLayerBuffer() noexcept { return _layer_buffer; }

    [[nodiscard]]
    SceneBuffer& getSceneBuffer() noexcept { return _scene_buffer; }

    // Changes scene using scene_id
    void setCurrentScene(std::string_view scene_name) noexcept;

    // Returns the active Scene
    [[nodiscard]]
    std::unique_ptr<Scene>& getCurrentScene() noexcept;

    // Returns true if provided SceneID is the current Scene
    [[nodiscard]]
    constexpr bool isSceneCurrent(std::string_view scene_name) const noexcept
    { return _current_scene == scene_name; }

    // DEV: logs LayerBuffer, SceneBuffer and current Scene
    void logStats() const noexcept;
};

} // namespace dull::core
