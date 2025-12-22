#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/core/scene_system.hpp"

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void SceneProcessor::iStart() { getCurrentScene()->iStart(); }

void SceneProcessor::iProcess() { getCurrentScene()->iProcess(); }

void SceneProcessor::iFixedProcess() { getCurrentScene()->iFixedProcess(); }

void SceneProcessor::setCurrentScene(std::string_view scene_name) noexcept
{
    if (scene_name == _current_scene) return; // No changes

    ZASSERT(
        _scene_buffer.hasScene(scene_name),
        "Scene '{}' not loaded into SceneBuffer", scene_name
    );

    _IF_LOG ZINFO(
        "Current Scene changed from '{}' to '{}'",
        _current_scene, scene_name
    );

    _current_scene = scene_name;

    // Only when running; Unless SceneSystem::_active() is called within App::run()
    if (App::instance().getHandle().isRunning()) iStart();
}

[[nodiscard]]
std::unique_ptr<Scene>& SceneProcessor::getCurrentScene() noexcept
{
    return _scene_buffer.getScene(_current_scene);
}

void SceneProcessor::logStats() const noexcept
{
    ZTRC_S("Logging SceneSystem");
    ZDBG("Current Scene = {}", _current_scene);

    _layer_buffer.logStats();
    _scene_buffer.logStats();
}

#undef _IF_LOG

} // namespace dull::core
