#pragma once

#include "engine/util/transform.hpp"
#include "engine/util/color.hpp"

namespace dull::render {

    using ZIndex = uint32_t;

    #define _BUILD_FN(_type, _name, _param_type, _param_name, _member) \
        [[nodiscard]] _type _name(_param_type _param_name) && { this->_member = _param_name; return std::move(*this); }

    struct DrawContext {
        util::Transform2D transform   {};
        util::Color       tintOverlay {color::WHITE};
        ZIndex            zAxisIndex  {0};

        _BUILD_FN(DrawContext, WithTransform, util::Transform2D, transform, transform)
        _BUILD_FN(DrawContext, WithTintOverlay, util::Color, tintOverlay, tintOverlay)
        _BUILD_FN(DrawContext, WithZAxisIndex, ZIndex, zAxisIndex, zAxisIndex)
    };

    struct ShapeContext {
        util::Color fillColor        {color::WHITE};
        util::Color outlineColor     {color::BLACK};
        float       outlineThinkness {0.0F};

        [[nodiscard]] bool HasOutline() const noexcept { return this->outlineThinkness > 0.0F; }

        _BUILD_FN(ShapeContext, WithFillColor, util::Color, fillColor, fillColor)
        _BUILD_FN(ShapeContext, WithOutlineColor, util::Color, outlineColor, outlineColor)
        _BUILD_FN(ShapeContext, WithOutlineThinkness, float, outlineThinkness, outlineThinkness)
    };

    struct TextContext {
        rl::Font    font     {rl::GetFontDefault()};
        zen::vec2   origin   {0};
        float       spacing  {2.0F};

        _BUILD_FN(TextContext, WithFont, rl::Font, font, font)
        _BUILD_FN(TextContext, WithOrigin, zen::vec2, origin, origin)
        _BUILD_FN(TextContext, WithSpacing, float, spacing, spacing)
    };

    #undef _BUILD_FN

} // namespace dull::render
