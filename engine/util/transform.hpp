#pragma once

#include <zen/math/angle.hpp>
#include <zen/math/vec2.hpp>

namespace dull::util {

    struct Transform2D final {
        zen::vec2  position {0};
        zen::angle rotation {zen::angle::from_deg(0)};
        zen::vec2  scale    {1};
    };

} // namespace dull::util
