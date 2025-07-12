#pragma once

#include <cstdint>

/// A singleton class for managing time-related information in the application.
class TimeSystem {
private:
  friend class App;

private:
  float _delta_time = 0.0f;
  float _time_scale = 1.0f;
  bool _is_paused = false;

private:
  TimeSystem() = default;
  ~TimeSystem() = default;

  TimeSystem(const TimeSystem &) = delete;
  TimeSystem(TimeSystem &&) = delete;
  TimeSystem &operator=(const TimeSystem &) = delete;
  TimeSystem &operator=(TimeSystem &&) = delete;

  inline void _updateInfo(float delta_time) noexcept { _delta_time = delta_time * _time_scale; }

public:
  [[nodiscard]] static inline TimeSystem &instance() noexcept {
    static TimeSystem instance;
    return instance;
  }

  inline void setTimeScale(float scale) noexcept { _time_scale = scale > 0.0f ? scale : 0.0f; }

  [[nodiscard]] inline float deltaTime() const noexcept { return _delta_time; }
  [[nodiscard]] inline float timeScale() const noexcept { return _time_scale; }
  [[nodiscard]] inline bool isPaused() const noexcept { return _is_paused; }

  [[nodiscard]] inline uint64_t fps() const noexcept {
    return (_delta_time > 0.0f) ? static_cast<uint64_t>(1.0f / _delta_time) : 0;
  }

  inline void pause() noexcept { _is_paused = true; }
  inline void unpause() noexcept { _is_paused = false; }
  inline void togglePause() noexcept { _is_paused = !_is_paused; }
};
