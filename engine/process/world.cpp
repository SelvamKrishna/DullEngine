#include "engine/core/app.hpp"
#include "engine/process/world.hpp"
#include "engine/config.hpp"

namespace dull::process {

misc::Buffer<Scene> World::s_scene_buf = {};

void World::iStart()        { getCurrentScene().iStart();        }
void World::iProcess()      { getCurrentScene().iProcess();      }
void World::iFixedProcess() { getCurrentScene().iFixedProcess(); }

void World::setCurrentScene(Scene::ID scene_id) noexcept
{
    if (scene_id == _current_scene) [[unlikely]] return;

    Scene* scene_ptr = s_scene_buf.find(scene_id);

    ZASSERT(
        scene_ptr != nullptr,
        "Scene '{}' not loaded into SceneBuffer", scene_id
    );

    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Current Scene changed to '{}'",
        scene_ptr->getName()
    );

    _current_scene = scene_id;

    if (DULL_HANDLE.isRunning()) [[likely]] getCurrentScene().iStart();
}

[[nodiscard]]
Scene& World::getCurrentScene() noexcept
{
    Scene* scene = s_scene_buf.find(_current_scene);
    ZASSERT(scene != nullptr, "Scene '{}' not yet added to Scene Buffer", _current_scene);
    return *scene;
}

} // namespace dull::process
