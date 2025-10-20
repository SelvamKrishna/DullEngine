#pragma once

#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>

namespace dull::util {

struct Rect {
	float x {0.0F};
	float y {0.0F};
	float w {1.0F};
	float h {1.0F};

/// --- Constructors ---

	constexpr Rect() noexcept = default;

	constexpr Rect(float x, float y, float width, float height) noexcept
	: x{x}, y{y}, w{width}, h{height} {}

	explicit constexpr Rect(const Vec2f& position, const Vec2f& dimension) noexcept
	: x{position.x}, y{position.y}, w{dimension.x}, h{dimension.y} {}

	[[nodiscard]] constexpr Rect(const Rectangle& rl_rect) noexcept
	: x{rl_rect.x}, y{rl_rect.y}, w{rl_rect.width}, h{rl_rect.height} {}

/// --- Accessors ---

	[[nodiscard]] constexpr Vec2f getPosition() const noexcept { return {x, y}; }
	[[nodiscard]] constexpr Vec2f getDimension() const noexcept { return {w, h}; }

/// --- Modifiers ---

	constexpr void move(const Vec2f& position_offset) noexcept {
		x += position_offset.x;
		y += position_offset.y;
	}

	constexpr void scale(const Vec2f& scale_multiplier) noexcept {
		w *= scale_multiplier.x;
		h *= scale_multiplier.y;
	}

/// --- Collision ---

  [[nodiscard]] bool containsPoint(const Vec2f& point) const noexcept {
    return CheckCollisionPointRec(point, *this);
  }

  [[nodiscard]] bool intersectsRec(const Rect& other) const noexcept {
    return CheckCollisionRecs(*this, other);
  }

/// --- Conversion ---

	[[nodiscard]] constexpr operator Rectangle() const noexcept { return Rect { x, y, w, h }; }

};

} // namespace dull::util