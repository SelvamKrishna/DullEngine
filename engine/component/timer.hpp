#pragma once

namespace dull::component {

    struct Timer {
    private:
        double _timeMeasure {1.0};
        double _timeStarted {0.0};
        bool   _isActive    {false};
        bool   _isLooping   {false};

    public:
        explicit Timer(double measureTime, bool isLooping = false) noexcept;

        void Start() noexcept;
        void Stop() noexcept;

        [[nodiscard]] double GetElapsed() const noexcept;
        [[nodiscard]] constexpr bool IsActive () const noexcept { return this->_isActive;  }
        [[nodiscard]] constexpr bool IsLooping() const noexcept { return this->_isLooping; }
        [[nodiscard]] bool IsOver() noexcept;

        void SetLooping(bool isLooping) noexcept;
        void SetMeasureTime(double measureTime) noexcept;
    };

} // namespace dull::component
