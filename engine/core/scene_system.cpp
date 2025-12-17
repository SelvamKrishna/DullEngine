#include "engine/core/scene_system.hpp"
#include "engine/core/app.hpp"

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void SceneSystem::_activate() { getCurrentScene()->_activate(); }

void SceneSystem::_process() { getCurrentScene()->_process(); }

void SceneSystem::_fixedProcess() { getCurrentScene()->_fixedProcess(); }

void SceneSystem::setCurrentScene(config::SceneID scene_id) noexcept
{
    if (scene_id == _current_scene) return; // No changes

    ZASSERT(
        static_cast<size_t>(scene_id) < _scene_buffer.sceneCount(),
        "Scene index '{}' out of range in SceneBuffer", typeid(scene_id).name()
    );

    _IF_LOG ZINFO(
        "Current Scene changed from '{}' to '{}'",
        static_cast<size_t>(_current_scene), static_cast<size_t>(scene_id)
    );

    _current_scene = scene_id;

    // Only when running; Unless SceneSystem::_active() is called within App::run()
    if (DULL_HANDLE.isRunning()) _activate();
}

[[nodiscard]]
std::unique_ptr<Scene>& SceneSystem::getCurrentScene() noexcept
{
    return _scene_buffer.getScene(_current_scene);
}

void SceneSystem::logStats() const noexcept
{
    ZTRC_S("Logging SceneSystem");
    ZVAR(size_t(SceneSystem::_current_scene));

    _layer_buffer.logStats();
    _scene_buffer.logStats();
}

#undef _IF_LOG

} // namespace dull::core
