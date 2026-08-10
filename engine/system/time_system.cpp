#include "engine/system/time_system.hpp"

#include <zen/math/utility.hpp>

namespace dull::system {

    void TimeSystem::_UpdateDeltaTime(double frameTime) noexcept
    {
        frameTime = zen::clamp(frameTime, 0.0, 0.25);
        this->_deltaTime = frameTime;
        this->_accumulator += frameTime;
    }

    bool TimeSystem::_TryConsumeAccumulated() noexcept
    {
        if (this->_accumulator < TimeSystem::FIXED_TICK_INTERVAL) return false;
        this->_accumulator -= TimeSystem::FIXED_TICK_INTERVAL;
        return true;
    }

} // namespace dull::system
