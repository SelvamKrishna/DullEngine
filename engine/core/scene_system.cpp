#include "engine/core/scene_system.hpp"

namespace dull::core {

#define _FOR_ALL_ACTIVE_LAYERS \
    for (auto& layer : current_scene.getActiveLayers())

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

#undef _FOR_ALL_ACTIVE_LAYERS

} // namespace dull::core
