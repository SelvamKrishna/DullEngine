#pragma once

#include "engine/config.hpp"

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::system {

    struct TimeSystem final {
        friend core::Engine;

    private:
        double _deltaTime;
        double _accumulator;

        explicit TimeSystem() = default;
        ~TimeSystem() = default;

        void _UpdateDeltaTime(double frameTime) noexcept;
        bool _TryConsumeAccumulated() noexcept;

    public:
        static constexpr double FIXED_TICK_INTERVAL = 1.0 / config::TICKS_PER_SECOND;

        constexpr TimeSystem(TimeSystem&&)                 noexcept = delete;
        constexpr TimeSystem(const TimeSystem&)            noexcept = delete;
        constexpr TimeSystem& operator=(TimeSystem&&)      noexcept = delete;
        constexpr TimeSystem& operator=(const TimeSystem&) noexcept = delete;

        [[nodiscard]] double GetDeltaTime() const noexcept { return _deltaTime; }
    };

} // namespace dull::system
