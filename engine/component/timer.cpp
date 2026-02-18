#include "engine/component/timer.hpp"

#include <vendor/raylib.h>

namespace dull::component {

Timer::Timer(double measureTime, bool isLooping) noexcept
    : _measureTime {measureTime}, _isLooping {isLooping}
{}

void Timer::Start() noexcept
{
    this->_isActive    = true;
    this->_startedTime = rl::GetTime();
}

void Timer::Stop() noexcept { this->_isActive = false; }

[[nodiscard]] double Timer::GetElapsed() const noexcept
{
    return this->IsActive() ? rl::GetTime() - this->_startedTime : 0.0;
}

[[nodiscard]] bool Timer::IsOver() noexcept
{
    if (!this->IsActive()) return true;

    double elapsedTime = rl::GetTime() - this->_startedTime;

    if (elapsedTime > this->_measureTime)
    {
        this->IsLooping() ? this->Start() : this->Stop();
        return true;
    }

    return false;
}

void Timer::SetLooping(bool isLooping) noexcept
{
    if (this->IsLooping() == isLooping) return;
    this->Stop();
    this->_isLooping = isLooping;
}

void Timer::SetMeasureTime(double measureTime) noexcept
{
    this->Stop();
    this->_measureTime = measureTime;
}

} // namespace dull::component
