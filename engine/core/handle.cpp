#include "engine/core/app.hpp"
#include "engine/core/handle.hpp"

namespace dull::core {

static App* s_app_ins = nullptr;

void Handle::_init() noexcept
{
    s_app_ins = &App::instance();
    _state = ProgramState::Initial;
}

SceneSystem& Handle::sceneSystem() noexcept
{
    return s_app_ins->_scene_sys;
}

const SceneSystem& Handle::sceneSystem() const noexcept
{
    return s_app_ins->_scene_sys;
}

EventBus& Handle::eventBus() noexcept
{
    return s_app_ins->_event_bus;
}

const EventBus& Handle::eventBus() const noexcept
{
    return s_app_ins->_event_bus;
}

} // namespace dull::core
