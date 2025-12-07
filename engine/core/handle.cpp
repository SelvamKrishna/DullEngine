#include "engine/core/app.hpp"
#include "engine/core/handle.hpp"

namespace dull::core {

static App* s_app_ins = nullptr;

void Handle::_init() const noexcept
{
    s_app_ins = &App::instance();
}
} // namespace dull::core
