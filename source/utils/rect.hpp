#pragma once

#include "vec2.hpp"

#include "../../vendor/raylib.h"

struct Rect {
public:
    float x, y, width, height;

    constexpr Rect() noexcept : x(0.F), y(0.F), width(0.F), height(0.F) {}

    constexpr Rect(Vec2 position, Vec2 size) noexcept
        : x(position.x)
        , y(position.y)
        , width(size.x)
        , height(size.y) {}

    constexpr Rect(float x, float y, float width, float height) noexcept
        : x(x)
        , y(y)
        , width(width)
        , height(height) {}

    // From raylib::Rectangle
    constexpr Rect(const Rectangle& rect) noexcept
        : x(rect.x)
        , y(rect.y)
        , width(rect.width)
        , height(rect.height) {}

    // To raylib::Rectangle
    constexpr operator Rectangle() const noexcept { return {x, y, width, height}; }
};