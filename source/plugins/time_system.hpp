#pragma once

#include "../core/constants.hpp"

#include <cstdint>

class TimeSystem {
	friend class App;

private:
	float _delta_time = 0.0F;
	float _time_scale = 1.0F;
	bool _is_paused = false;

	explicit TimeSystem() = default;
	~TimeSystem() = default;

	void _updateInfo(float delta_time) noexcept { _delta_time = delta_time * _time_scale; }

public:
	TimeSystem(const TimeSystem &) = delete;
	TimeSystem(TimeSystem &&) = delete;
	TimeSystem &operator=(const TimeSystem &) = delete;
	TimeSystem &operator=(TimeSystem &&) = delete;

	static constexpr float FIXED_FRAME_RATE = GameInfo::FIXED_FRAME_RATE;
	static constexpr float FIXED_DELTA_TIME = 1.0F / FIXED_FRAME_RATE;

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