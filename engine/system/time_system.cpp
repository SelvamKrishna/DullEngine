#include "engine/system/time_system.hpp"

#include <vendor/raylib.h>

namespace dull::system {

double TimeSystem::_sDeltaTime = 0.0;

bool TimeSystem::_IsFixedProcess() noexcept
{
    static double sAccumulatedTime = 0;

    TimeSystem::_sDeltaTime = rl::GetFrameTime();
    sAccumulatedTime += TimeSystem::_sDeltaTime;

    if (sAccumulatedTime > TimeSystem::FIXED_TICK_INTERVAL) [[unlikely]]
    {
        sAccumulatedTime -= TimeSystem::FIXED_TICK_INTERVAL;
        return true;
    }

    return false;
}

} // namespace dull::system
