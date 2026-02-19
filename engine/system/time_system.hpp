#pragma once

#include "engine/config.hpp"

// Forward Declaration
namespace dull::core   { struct App;          }
namespace dull::system { struct SystemHandle; }

namespace dull::system {

// ---
// Provides time related data
// ---
struct TimeSystem final {
    friend core::App;
    friend SystemHandle;

private:
    static double _sDeltaTime;

    explicit TimeSystem() = default;
    ~TimeSystem() = default;

    [[nodiscard]] bool _IsFixedProcess() noexcept;

public:
    static constexpr double FIXED_TICK_INTERVAL = 1.0 / config::TICKS_PER_SECOND;

    constexpr TimeSystem(TimeSystem&&)                 noexcept = delete;
    constexpr TimeSystem(const TimeSystem&)            noexcept = delete;
    constexpr TimeSystem& operator=(TimeSystem&&)      noexcept = delete;
    constexpr TimeSystem& operator=(const TimeSystem&) noexcept = delete;

    [[nodiscard]] double GetDeltaTime() const noexcept { return _sDeltaTime; }
};

} // namespace dull::system
