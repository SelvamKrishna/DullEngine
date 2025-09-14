#pragma once

#include "app/constants.hpp"
#include "engine/utils/vec2.hpp"

#include "vendor/raylib.h"

/// Wrapper for raylib::Camera2D
struct camera2d {
public:
    vec2 offset { vec2::unit() };
    vec2 target { vec2::unit() };
    float rotation { 0.0F };
    float zoom { 1.0F };

	explicit constexpr camera2d() = default;

	// From raylib::Camera2D
	constexpr camera2d(const Camera2D& cam) noexcept
	: offset(cam.offset)
	, target(cam.target)
	, rotation(cam.rotation)
	, zoom(cam.zoom) {}

	// To raylib::Camera2D
	constexpr operator Camera2D() const noexcept {
		return {
			offset,
			target,
			rotation,
			zoom
		};
	}

	static constexpr camera2d standard() noexcept {
		camera2d cam;
		cam.offset = {
			GameInfo::WINDOW_WIDTH / 2.0F,
			GameInfo::WINDOW_HEIGHT / 2.0F
		};

		return cam;
	}
};

/// Wrapper for raylib::Camera2D with locked target reference
struct camera2d_locked {
public:
    vec2 offset { vec2::unit() };
    vec2& target_ref;
    float rotation { 0.0F };
    float zoom { 1.0F };

	explicit constexpr camera2d_locked(vec2& target_ref) : target_ref(target_ref) {}

	// To raylib::Camera2D
	constexpr operator Camera2D() const noexcept {
		return {
			offset,
			target_ref,
			rotation,
			zoom
		};
	}
};