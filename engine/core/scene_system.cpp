#include "engine/core/scene_system.hpp"
#include "engine/core/app.hpp"

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_LAYER_SYS)

#define _FOR_ALL_ACTIVE_LAYERS \
    for (auto& layer : getCurrentScene()->getActiveLayers())

void SceneSystem::_activate()
{
    _FOR_ALL_ACTIVE_LAYERS _layer_buffer.getLayer(layer)->_activate();
}

void SceneSystem::_process()
{
    _FOR_ALL_ACTIVE_LAYERS _layer_buffer.getLayer(layer)->_process();
}

void SceneSystem::_fixedProcess()
{
    _FOR_ALL_ACTIVE_LAYERS _layer_buffer.getLayer(layer)->_fixedProcess();
}

void SceneSystem::setCurrentScene(config::SceneID scene_id) noexcept
{
    if (scene_id == _current_scene) return;

    ZASSERT(
        static_cast<size_t>(scene_id) < _scene_buffer.sceneCount(),
        "Scene index '{}' out of range in SceneBuffer", typeid(scene_id).name()
    );

    _current_scene = scene_id;
    if (DULL_HANDLE.getProgramState() == ProgramState::Process) _activate();
}

[[nodiscard]]
std::unique_ptr<Scene>& SceneSystem::getCurrentScene() noexcept
{
    return _scene_buffer.getScene(_current_scene);
}

#undef _FOR_ALL_ACTIVE_LAYERS
#undef _IF_LOG

} // namespace dull::core
