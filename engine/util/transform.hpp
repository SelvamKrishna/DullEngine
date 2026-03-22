#pragma once

#include "engine/util/vec2.hpp"

#include <vendor/zenutil/zen/core/macros.hpp>
#include <vendor/zenutil/zen/math/angle.hpp>

namespace dull::util {

    struct Transform2D final {
        util::Vec2f      position = util::Vec2f::Zero();
        zen::math::Angle rotation = zen::math::Angle::FromDegrees(0);
        util::Vec2f      scale = util::Vec2f::One();
    };

    static constexpr Transform2D DEFAULT_TRANSFORM_2D = {};

} // namespace dull::util
