#pragma once

#include "engine/utils/vec2.hpp"

#include "vendor/raylib.h"

struct rect {
public:
	float x, y, width, height;

	constexpr rect() noexcept : x(0.F), y(0.F), width(0.F), height(0.F) {}

	constexpr rect(vec2 position, vec2 size) noexcept
	: x(position.x)
	, y(position.y)
	, width(size.x)
	, height(size.y) {}

	constexpr rect(float x, float y, float width, float height) noexcept
	: x(x)
	, y(y)
	, width(width)
	, height(height) {}

	// From raylib::Rectangle
	constexpr rect(const Rectangle& rect) noexcept
	: x(rect.x)
	, y(rect.y)
	, width(rect.width)
	, height(rect.height) {}

	// To raylib::Rectangle
	constexpr operator Rectangle() const noexcept { return {x, y, width, height}; }
};