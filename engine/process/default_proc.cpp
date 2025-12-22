#include "engine/config.hpp"

#include "engine/core/app.hpp"
#include "engine/process/default_proc.hpp"

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void DefaultProcessor::iStart()        { getCurrentScene().iStart();        }
void DefaultProcessor::iProcess()      { getCurrentScene().iProcess();      }
void DefaultProcessor::iFixedProcess() { getCurrentScene().iFixedProcess(); }

void DefaultProcessor::setCurrentScene(std::string_view scene_name) noexcept
{
    if (scene_name == _current_scene) return;

    ZASSERT( // If Scene not laready loaded into buffer
        _scene_buf.hasData(scene_name),
        "Scene '{}' not loaded into SceneBuffer", scene_name
    );

    _IF_LOG ZINFO(
        "Current Scene changed from '{}' to '{}'",
        _current_scene, scene_name
    );

    _current_scene = scene_name;

    if (DULL_HANDLE.isRunning()) [[likely]] getCurrentScene().iStart();
}

[[nodiscard]]
Scene& DefaultProcessor::getCurrentScene() noexcept
{
    return _scene_buf.getData(_current_scene);
}

void DefaultProcessor::logStats() const noexcept
{
    ZTRC_S("Logging SceneSystem");
    ZDBG("Current Scene = {}", _current_scene);
    ZTODO("Scene Buffer logging");
}

#undef _IF_LOG

} // namespace dull::process
