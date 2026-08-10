#pragma once

#include "engine/util/adapter.hpp"

#include <zen/math/vec2.hpp>
#include <vendor/raylib.h>

namespace dull::util {

    struct Rect {
        float x {0.0F};
        float y {0.0F};
        float w {1.0F};
        float h {1.0F};

        constexpr Rect() noexcept = default;

        constexpr Rect(float x, float y, float width, float height) noexcept
            : x {x}, y {y}, w {width}, h {height}
        {}

        constexpr Rect(const zen::vec2& position, const zen::vec2& dimension) noexcept
            : x {position.x}, y {position.y}, w {dimension.x}, h {dimension.y}
        {}

        [[nodiscard]] constexpr Rect(const rl::Rectangle& rlRect) noexcept
            : x {rlRect.x}, y {rlRect.y}, w {rlRect.width}, h {rlRect.height}
        {}

        [[nodiscard]] constexpr zen::vec2 GetPosition () const noexcept { return {this->x, this->y}; }
        [[nodiscard]] constexpr zen::vec2 GetDimension() const noexcept { return {this->w, this->h}; }

        constexpr void Move(const zen::vec2& positionOffset) noexcept
        {
            this->x += positionOffset.x;
            this->y += positionOffset.y;
        }

        constexpr void Scale(const zen::vec2& scaleMulitplier) noexcept
        {
            this->w *= scaleMulitplier.x;
            this->h *= scaleMulitplier.y;
        }

        [[nodiscard]] bool CollidesWith(const zen::vec2& point) const noexcept
        {
            return rl::CheckCollisionPointRec(rl_cast(point), *this);
        }

        [[nodiscard]] bool CollidesWith(const Rect& other) const noexcept
        {
            return rl::CheckCollisionRecs(*this, other);
        }

        [[nodiscard]] constexpr operator rl::Rectangle() const noexcept
        {
            return { this->x, this->y, this->w, this->h };
        }
    };

} // namespace dull::util
