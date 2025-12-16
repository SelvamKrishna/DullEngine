#pragma once

#include "engine/config.hpp"
#include "engine/core/layer_buffer.hpp"
#include "engine/core/scene_buffer.hpp"

namespace dull::core {

class SceneSystem final {
    friend class App;

private:
    LayerBuffer _layer_buffer;
    SceneBuffer _scene_buffer;

    config::SceneID _current_scene;

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

    void setCurrentScene(config::SceneID scene_id) noexcept;

    [[nodiscard]]
    std::unique_ptr<Scene>& getCurrentScene() noexcept;
};

} // namespace dull::core
