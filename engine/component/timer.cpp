#include "engine/component/timer.hpp"

#include <vendor/raylib.h>

namespace dull::component {

Timer::Timer(double timeToMeasure) noexcept : _measureTime {timeToMeasure} {}

void Timer::Start() noexcept { this->_startedTime = rl::GetTime(); }
void Timer::Stop() noexcept { this->_startedTime = -1.0; }

[[nodiscard]] bool Timer::IsActive() const noexcept { return this->_startedTime >= 0.0; }

[[nodiscard]] bool Timer::IsOver() noexcept
{
    if (!this->IsActive()) return true;

    double currentTime = rl::GetTime();
    double elapsedTime = currentTime - this->_startedTime;

    if (elapsedTime > _measureTime)
    {
        this->Stop();
        return true;
    }

    return false;
}

} // namespace dull::component
