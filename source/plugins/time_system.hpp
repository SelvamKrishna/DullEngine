#pragma once

#include <cstdint>

/// A class for managing time-related information in the application.
class TimeSystem {
    friend class App;

private:
    static constexpr float FIXED_FRAME_RATE = 60.0F;
    static constexpr float FIXED_DELTA_TIME = 1.0F / FIXED_FRAME_RATE;

    float _delta_time = 0.0F;
    float _time_scale = 1.0F;
    bool _is_paused = false;

    TimeSystem() = default;
    ~TimeSystem() = default;

    void _updateInfo(float delta_time) noexcept { _delta_time = delta_time * _time_scale; }

public:
    TimeSystem(const TimeSystem &) = delete;
    TimeSystem(TimeSystem &&) = delete;
    TimeSystem &operator=(const TimeSystem &) = delete;
    TimeSystem &operator=(TimeSystem &&) = delete;

    [[nodiscard]] constexpr static float fixedFrameRate() noexcept { return FIXED_FRAME_RATE; }
    [[nodiscard]] constexpr static float fixedDeltaTime() noexcept { return FIXED_DELTA_TIME; }

    constexpr void setTimeScale(float scale) noexcept { _time_scale = scale > 0.0F ? scale : 0.0F; }

    [[nodiscard]] constexpr float deltaTime() const noexcept { return _delta_time; }
    [[nodiscard]] constexpr float timeScale() const noexcept { return _time_scale; }
    [[nodiscard]] constexpr bool isPaused() const noexcept { return _is_paused; }

    [[nodiscard]] constexpr uint64_t fps() const noexcept {
        return _delta_time > 0.0F ? static_cast<uint64_t>(1.0F / _delta_time) : 0;
    }

    constexpr void pause() noexcept { _is_paused = true; }
    constexpr void unpause() noexcept { _is_paused = false; }
    constexpr void togglePause() noexcept { _is_paused = !_is_paused; }
};