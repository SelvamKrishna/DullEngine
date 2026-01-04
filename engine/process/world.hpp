#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/misc/processor.hpp"
#include "engine/process/layer.hpp"
#include "engine/process/scene.hpp"

namespace dull::process {

// =======================
// Manager of all scene related logic
// =======================
class World : private misc::IProcessor {
    friend core::App;

private:
    static misc::Buffer<Scene> s_scene_buf;               //< Collection of all loaded Scenes
    Scene::ID::Raw _current_scene = Scene::ID::invalid(); //< Scene currently active

    explicit World() = default;
    ~World() = default;

    void iStart()        final;
    void iProcess()      final;
    void iFixedProcess() final;

public:
    [[nodiscard]]
    static misc::Buffer<Scene>& getSceneBuffer() noexcept { return s_scene_buf; }

    // Changes scene using scene_id
    void setCurrentScene(Scene::ID scene_id) noexcept;

    // Returns the active Scene
    [[nodiscard]]
    Scene& getCurrentScene() noexcept;

    // Returns true if provided SceneID is the current Scene
    [[nodiscard]]
    bool isSceneCurrent(Scene::ID scene_id) const noexcept
    { return _current_scene == scene_id; }
};

} // namespace dull::process
