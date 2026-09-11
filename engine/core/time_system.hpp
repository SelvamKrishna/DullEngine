#pragma once

#include "engine/config.hpp"

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::core {

    struct TimeSystem final {
        friend core::Engine;

    private:
        double _deltaTime;
        double _unscaledDeltaTime;
        double _timeScale   {1.0};
        double _accumulator {0.0};
        double _gameTime    {0.0};

        explicit TimeSystem() = default;
        ~TimeSystem() = default;

        void _Update(double frameTime) noexcept;
        bool _ShouldFixedUpdate() noexcept;

    public:
        static constexpr double FIXED_TICK_INTERVAL = 1.0 / config::TICKS_PER_SECOND;

        constexpr TimeSystem(TimeSystem&&)                 noexcept = delete;
        constexpr TimeSystem(const TimeSystem&)            noexcept = delete;
        constexpr TimeSystem& operator=(TimeSystem&&)      noexcept = delete;
        constexpr TimeSystem& operator=(const TimeSystem&) noexcept = delete;

        [[nodiscard]] constexpr double GetDelta() const noexcept { return this->_deltaTime; }
        [[nodiscard]] constexpr double GetUnscaledDelta() const noexcept { return this->_unscaledDeltaTime; }
        [[nodiscard]] constexpr double GetGameTime() const noexcept { return this->_gameTime; }
        [[nodiscard]] constexpr double GetTimeScale() const noexcept { return this->_timeScale; }

        void SetTimeScale(double scale);
    };

} // namespace dull::core
