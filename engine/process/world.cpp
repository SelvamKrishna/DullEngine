#include "engine/config.hpp"

#include "engine/core/app.hpp"
#include "engine/process/world.hpp"

namespace dull::process {

misc::Buffer<Scene> World::s_scene_buf = {};

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void World::iStart()        { getCurrentScene().iStart();        }
void World::iProcess()      { getCurrentScene().iProcess();      }
void World::iFixedProcess() { getCurrentScene().iFixedProcess(); }

void World::setCurrentScene(Scene::ID scene_id) noexcept
{
    if (scene_id == _current_scene) return;

    ZASSERT( // If Scene not laready loaded into buffer
        s_scene_buf.find(scene_id) != nullptr,
        "Scene '{}' not loaded into SceneBuffer", scene_id
    );

    _IF_LOG ZINFO(
        "Current Scene changed from '{}' to '{}'",
        s_scene_buf.find(_current_scene)->getName(),  s_scene_buf.find(scene_id)->getName()
    );

    _current_scene = scene_id;

    if (DULL_HANDLE.isRunning()) [[likely]] getCurrentScene().iStart();
}

[[nodiscard]]
Scene& World::getCurrentScene() noexcept
{
    Scene* scene = s_scene_buf.find(_current_scene);
    ZASSERT(scene != nullptr, "Scene '{}' not yet added to Scene Buffer", _current_scene);
    return *s_scene_buf.find(_current_scene);
}

#undef _IF_LOG

} // namespace dull::process
