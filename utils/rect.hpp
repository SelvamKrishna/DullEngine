#pragma once

#include "../vendor/raylib.h"
#include "vec2.hpp"

class Rect {
public:
  float x, y, width, height;

public:
  constexpr Rect() noexcept : x(0.f), y(0.f), width(0.f), height(0.f) {}

  constexpr Rect(Vec2 position, Vec2 size) noexcept
  : x(position.x), y(position.y), width(size.x), height(size.y) {}

  constexpr Rect(float x, float y, float width, float height) noexcept
  : x(x), y(y), width(width), height(height) {}

  // Constructor from raylib::Rectangle
  constexpr operator Rectangle() const noexcept { return {x, y, width, height}; }

  // Copy from raylib::Rectangle to Rect
  constexpr Rect(const Rectangle &rect) noexcept
  : x(rect.x), y(rect.y), width(rect.width), height(rect.height) {}
};