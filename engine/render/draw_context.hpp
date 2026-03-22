#pragma once

#include "engine/util/transform.hpp"
#include "engine/util/color.hpp"

namespace dull::render {

    struct DrawContext {
        const util::Transform2D* TRANSFORM_PTR = &util::DEFAULT_TRANSFORM_2D;
        util::Color tintOverlay = util::Color::White();
        uint32_t    zAxisIndex  = 0;
    };

    static constexpr DrawContext DEFAULT_DRAW_CONTEXT = {};

} // namespace dull::render
