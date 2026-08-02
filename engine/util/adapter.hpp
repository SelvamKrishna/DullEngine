#pragma once

#include <zen/math/vec2.hpp>
#include <zen/math/vec3.hpp>

#include <vendor/raylib.h>

namespace dull::util {

    #define _RL_CONV_FN(_from, _to) \
        [[nodiscard]] inline constexpr _to toRL(const _from& e)

    _RL_CONV_FN(zen::vec2, rl::Vector2) { return {e.x, e.y}; }
    _RL_CONV_FN(zen::vec3, rl::Vector3) { return {e.x, e.y, e.z}; }

    #undef _RL_CONV_FN

} // namespace dull::util

#define rl_cast ::dull::util::toRL

#ifdef NDEBUG
#define ON_DBG if constexpr (false)
#else
#define ON_DBG if constexpr (true)
#endif
