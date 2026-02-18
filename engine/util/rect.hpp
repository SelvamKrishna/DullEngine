#pragma once

#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>

namespace dull::util {

// ---
// Data representation of a Rectangle
// ---
struct Rect {
    float x {0.0F};
    float y {0.0F};
    float w {1.0F};
    float h {1.0F};

// --- Constructors ---

    constexpr Rect() noexcept = default;

    constexpr Rect(float x, float y, float width, float height) noexcept
        : x {x}, y {y}, w {width}, h {height}
    {}

    constexpr Rect(const Vec2f& position, const Vec2f& dimension) noexcept
        : x {position.x}, y {position.y}, w {dimension.x}, h {dimension.y}
    {}

    [[nodiscard]] constexpr Rect(const rl::Rectangle& rlRect) noexcept
        : x {rlRect.x}, y {rlRect.y}, w {rlRect.width}, h {rlRect.height}
    {}

// --- Accessors ---

    [[nodiscard]] constexpr Vec2f GetPosition () const noexcept { return {this->x, this->y}; }
    [[nodiscard]] constexpr Vec2f GetDimension() const noexcept { return {this->w, this->h}; }

// --- Modifiers ---

    constexpr void Move(const Vec2f& positionOffset) noexcept
    {

        this->x += positionOffset.x;
        this->y += positionOffset.y;
    }

    constexpr void Scale(const Vec2f& scaleMulitplier) noexcept
    {
        this->w *= scaleMulitplier.x;
        this->h *= scaleMulitplier.y;
    }

// --- Collision ---

    [[nodiscard]] bool CollidesWith(const Vec2f& point) const noexcept
    {
        return rl::CheckCollisionPointRec(point, *this);
    }

    [[nodiscard]] bool CollidesWith(const Rect& other) const noexcept
    {
        return rl::CheckCollisionRecs(*this, other);
    }

// --- Conversion ---

    [[nodiscard]] constexpr operator rl::Rectangle() const noexcept
    {
        return { this->x, this->y, this->w, this->h };
    }
};

} // namespace dull::util
