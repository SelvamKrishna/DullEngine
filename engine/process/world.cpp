#include "engine/config.hpp"

#include "engine/core/app.hpp"
#include "engine/process/world.hpp"

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void World::iStart()        { getCurrentScene().iStart();        }
void World::iProcess()      { getCurrentScene().iProcess();      }
void World::iFixedProcess() { getCurrentScene().iFixedProcess(); }

void World::setCurrentScene(std::string_view scene_name) noexcept
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

    if (dull::HANDLE.isRunning()) [[likely]] getCurrentScene().iStart();
}

[[nodiscard]]
Scene& World::getCurrentScene() noexcept
{
    return _scene_buf.getData(_current_scene);
}

void World::logStats() const noexcept
{
    ZTRC_S("Logging SceneSystem");
    ZDBG("Current Scene = {}", _current_scene);
    ZTODO("Scene Buffer logging");
}

#undef _IF_LOG

} // namespace dull::process
