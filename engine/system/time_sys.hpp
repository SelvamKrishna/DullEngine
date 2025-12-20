#pragma once

#include "engine/config.hpp"

// Forward Declaration
namespace dull::core { class App; }

namespace dull::sys {

// =======================
// Time System
// =======================
class TimeSystem final {
    friend class dull::core::App;

private:
    static double s_delta_time; //< Time between frames

    explicit TimeSystem() = default;
    ~TimeSystem() = default;

    // True every fixed frame; Updates s_delta_time
    [[nodiscard]]
    bool _isFixedProcess() noexcept;

public:
    static constexpr uint32_t FPS = config::FIXED_PROCESS_FPS;
    static constexpr double FIXED_PROCESS_INTERVAL = 1.0 / FPS;

    constexpr TimeSystem(TimeSystem&&)                 noexcept = delete;
    constexpr TimeSystem(const TimeSystem&)            noexcept = delete;
    constexpr TimeSystem& operator=(TimeSystem&&)      noexcept = delete;
    constexpr TimeSystem& operator=(const TimeSystem&) noexcept = delete;

    [[nodiscard]]
    double getDeltaTime() const noexcept { return s_delta_time; }
};

} // namespace dull::sys
