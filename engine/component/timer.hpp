#pragma once

namespace dull::component {

struct Timer {
private:
    double _measureTime = 1.0;
    double _startedTime = 0.0;
    bool   _isActive    = false;
    bool   _isLooping   = false;

public:
    explicit Timer(double measureTime, bool isLooping = false) noexcept;

    void Start() noexcept;
    void Stop() noexcept;

    [[nodiscard]] double GetElapsed() const noexcept;

    [[nodiscard]] bool IsActive () const noexcept { return this->_isActive;  }
    [[nodiscard]] bool IsLooping() const noexcept { return this->_isLooping; }

    [[nodiscard]] bool IsOver() noexcept;

    void SetLooping(bool isLooping) noexcept;
    void SetMeasureTime(double measureTime) noexcept;
};

} // namespace dull::component
