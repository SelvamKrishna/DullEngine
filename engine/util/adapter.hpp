#pragma once

#include <zen/math/vec2.hpp>
#include <zen/math/vec3.hpp>

#include <vendor/raylib.h>

namespace dull::util {
    #define RL_CONVERSION(_from, _to) \
        [[nodiscard]] inline constexpr _to toRL(const _from& e)

    RL_CONVERSION(zen::vec2, rl::Vector2) { return {e.x, e.y}; }
    RL_CONVERSION(zen::vec3, rl::Vector3) { return {e.x, e.y, e.z}; }

    #undef RL_CONVERSION
}

#define rl_cast ::dull::util::toRL
