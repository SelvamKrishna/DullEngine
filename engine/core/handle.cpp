#include "engine/core/app.hpp"
#include "engine/core/handle.hpp"

namespace dull::core {

static App* s_app_ins = nullptr;

void Handle::_init() noexcept
{
    s_app_ins = &App::instance();
    _state = ProgramState::Initial;
}

} // namespace dull::core
