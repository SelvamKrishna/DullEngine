#include "engine/system/time_system.hpp"

#include <vendor/raylib.h>

namespace dull::system {

double TimeSystem::s_delta_time = 0.0;

bool TimeSystem::_isFixedProcess() noexcept
{
    static double s_accum_time = 0;

    TimeSystem::s_delta_time = rl::GetFrameTime();
    s_accum_time += s_delta_time;

    if (s_accum_time > FIXED_PROCESS_INTERVAL) [[unlikely]]
    {
        s_accum_time -= FIXED_PROCESS_INTERVAL;
        return true;
    }

    return false;
}

} // namespace dull::system
