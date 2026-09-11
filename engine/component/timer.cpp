#include "engine/component/timer.hpp"

#include <vendor/raylib.h>

namespace dull::component {

    Timer::Timer(double measureTime, bool isLooping) noexcept
        : _timeMeasure {measureTime}, _isLooping {isLooping}
    {}

    void Timer::Start() noexcept
    {
        this->_isActive = true;
        this->_timeStarted = rl::GetTime();
    }

    void Timer::Stop() noexcept { this->_isActive = false; }

    [[nodiscard]] double Timer::GetElapsed() const noexcept
    {
        return this->IsActive() ? rl::GetTime() - this->_timeStarted : 0.0;
    }

    [[nodiscard]] bool Timer::IsOver() noexcept
    {
        if (!this->IsActive()) return true;

        double elapsedTime {rl::GetTime() - this->_timeStarted};

        if (elapsedTime > this->_timeMeasure)
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
        this->_timeMeasure = measureTime;
    }

} // namespace dull::component
