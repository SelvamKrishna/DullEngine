#include "engine/system/time_system.hpp"

#include <zen/math/utility.hpp>

namespace dull::system {

    void TimeSystem::_Update(double frameTime) noexcept
    {
        frameTime = zen::clamp(frameTime, 0.0, 0.25);
        this->_unscaledDeltaTime = frameTime;
        this->_deltaTime = frameTime * this->_timeScale;
        this->_accumulator += this->_deltaTime;
        this->_gameTime += this->_deltaTime;
    }

    bool TimeSystem::_ShouldFixedUpdate() noexcept
    {
        if (this->_accumulator < TimeSystem::FIXED_TICK_INTERVAL) return false;
        this->_accumulator -= TimeSystem::FIXED_TICK_INTERVAL;
        return true;
    }

    void TimeSystem::SetTimeScale(double scale)
    {
        static constexpr double MAX_TIME_SCALE {10.0};
        this->_timeScale = zen::clamp(scale, 0.0, MAX_TIME_SCALE);
    }

} // namespace dull::system
