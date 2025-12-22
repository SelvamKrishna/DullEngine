#include "engine/config.hpp"

#include "engine/core/app.hpp"
#include "engine/process/scene_processor.hpp"

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void SceneProcessor::iStart()        { getCurrentScene().iStart();        }
void SceneProcessor::iProcess()      { getCurrentScene().iProcess();      }
void SceneProcessor::iFixedProcess() { getCurrentScene().iFixedProcess(); }

void SceneProcessor::setCurrentScene(std::string_view scene_name) noexcept
{
    if (scene_name == _current_scene) return; // No changes

    ZASSERT(
        _scene_buffer.hasData(scene_name),
        "Scene '{}' not loaded into SceneBuffer", scene_name
    );

    _IF_LOG ZINFO(
        "Current Scene changed from '{}' to '{}'",
        _current_scene, scene_name
    );

    _current_scene = scene_name;

    if (DULL_HANDLE.isRunning()) [[likely]] iStart();
}

[[nodiscard]]
Scene& SceneProcessor::getCurrentScene() noexcept
{
    return _scene_buffer.getData(_current_scene);
}

void SceneProcessor::logStats() const noexcept
{
    ZTRC_S("Logging SceneSystem");
    ZDBG("Current Scene = {}", _current_scene);

    ZTODO("LayerBuffer and SceneBuffer logging");
    // _layer_buffer.logStats();
    // _scene_buffer.logStats();
}

#undef _IF_LOG

} // namespace dull::process
