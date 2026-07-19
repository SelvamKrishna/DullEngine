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

    struct ShapeContext {
        util::Color fillColor        = util::Color::White();
        util::Color outlineColor     = util::Color::Black();
        float       outlineThinkness = 0.0F;

        [[nodiscard]] bool HasOutline() const noexcept { return outlineThinkness > 0; }
    };

    static constexpr ShapeContext DEFAULT_SHAPE_CONTEXT = {};

} // namespace dull::render
