#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/misc/processor.hpp"
#include "engine/process/layer.hpp"
#include "engine/process/scene.hpp"

#include <string_view>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::process {

// =======================
// Manager of all scene related logic
// =======================
class DefaultProcessor : private misc::IProcessor {
    friend class core::App;

private:
    misc::Buffer<Scene> _scene_buf;  //< Collection of all loaded Scenes
    std::string_view _current_scene; //< Scene currently active

    explicit DefaultProcessor() = default;
    ~DefaultProcessor() = default;

    void iStart()        final;
    void iProcess()      final;
    void iFixedProcess() final;

public:
    [[nodiscard]]
    misc::Buffer<Scene>& getSceneBuffer() noexcept { return _scene_buf; }

    // Changes scene using scene_id
    void setCurrentScene(std::string_view scene_name) noexcept;

    // Returns the active Scene
    [[nodiscard]]
    Scene& getCurrentScene() noexcept;

    // Returns true if provided SceneID is the current Scene
    [[nodiscard]]
    constexpr bool isSceneCurrent(std::string_view scene_name) const noexcept
    { return _current_scene == scene_name; }

    // DEV: logs LayerBuffer, SceneBuffer and current Scene
    void logStats() const noexcept;
};

} // namespace dull::process
