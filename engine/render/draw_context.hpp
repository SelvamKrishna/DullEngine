#pragma once

#include "engine/util/transform.hpp"
#include "engine/util/color.hpp"

namespace dull::render {

    struct DrawContext {
        const util::Transform2D* TRANSFORM_PTR {&util::DEFAULT_TRANSFORM_2D};

        util::Color tintOverlay {color::WHITE};
        uint32_t    zAxisIndex  {0};
    };

    static constexpr DrawContext DEFAULT_DRAW_CONTEXT {};

    struct ShapeContext {
        util::Color fillColor        {color::WHITE};
        util::Color outlineColor     {color::BLACK};
        float       outlineThinkness {0.0F};

        [[nodiscard]] bool HasOutline() const noexcept { return this->outlineThinkness > 0.0F; }
    };

    static constexpr ShapeContext DEFAULT_SHAPE_CONTEXT {};

} // namespace dull::render
