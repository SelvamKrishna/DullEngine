#pragma once

#include "engine/util/transform.hpp"
#include "engine/util/color.hpp"

namespace dull::render {

    struct DrawContext {
        const util::Transform2D& TRANSFORM_PTR {};

        util::Color tintOverlay {color::WHITE};
        uint32_t    zAxisIndex  {0};
    };

    struct ShapeContext {
        util::Color fillColor        {color::WHITE};
        util::Color outlineColor     {color::BLACK};
        float       outlineThinkness {0.0F};

        [[nodiscard]] bool HasOutline() const noexcept { return this->outlineThinkness > 0.0F; }
    };

    struct TextContext {
        util::Color color    {color::WHITE};
        zen::vec2   position {0};
        rl::Font    font     {rl::GetFontDefault()};
        zen::vec2   origin   {0};
        zen::angle  rotation {zen::angle::from_deg(0)};
        float       spacing  {2.0F};
        float       fontSize {12.0F};
    };

} // namespace dull::render
