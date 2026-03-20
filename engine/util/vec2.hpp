#pragma once

#include <vendor/raylib.h>
#include <vendor/zenutil/zen/math/vec2.hpp>

namespace dull::util {

    template <typename ValueT>
    struct Vec2 : public zen::math::Vec2<ValueT> {
        using Base = zen::math::Vec2<ValueT>;
        using Base::Base;

        constexpr Vec2(const rl::Vector2& rlVec) noexcept
            : Base {static_cast<ValueT>(rlVec.x), static_cast<ValueT>(rlVec.y)}
        {}

        [[nodiscard]] constexpr operator rl::Vector2() const noexcept
        {
            return {static_cast<float>(this->x), static_cast<float>(this->y)};
        }
    };

    using Vec2f = Vec2<float>;
    using Vec2i = Vec2<int>;

}
