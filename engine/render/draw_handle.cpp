#include "engine/render/draw_handle.hpp"
#include "engine/util/adapter.hpp"

#include <zen/log.hpp>
#include <zen/math/vec2.hpp>

#include <vendor/raylib.h>

namespace dull::render {

    DrawHandle::DrawHandle()  { rl::BeginDrawing(); rl::ClearBackground(color::BLACK); }
    DrawHandle::~DrawHandle() { rl::EndDrawing(); }

    void DrawHandle::DrawRectangle(
        const util::Rect& rectangle,
        zen::angle rotation,
        const ShapeContext& shapeCtx
    ) const
    {
        rl::DrawRectanglePro(
            rectangle,
            rl_cast(rectangle.GetDimension() * 0.5f),
            rotation.as_deg(),
            shapeCtx.fillColor
        );

        if (!shapeCtx.HasOutline()) return;
        rl::DrawRectangleLinesEx(rectangle, shapeCtx.outlineThinkness, shapeCtx.outlineColor);
    }

    void DrawHandle::DrawCircle(
        const zen::vec2& position,
        float radius,
        const ShapeContext& shapeCtx
    ) const
    {
        if (shapeCtx.HasOutline()) rl::DrawCircleV(
            rl_cast(position), radius + shapeCtx.outlineThinkness, shapeCtx.outlineColor
        );

        rl::DrawCircleV(rl_cast(position), radius, shapeCtx.fillColor);
    }

    void DrawHandle::DrawLine(
        const zen::vec2& pointA,
        const zen::vec2& pointB,
        const ShapeContext& shapeCtx
    ) const
    {
        rl::DrawLineEx(
            rl_cast(pointA), rl_cast(pointB),
            shapeCtx.outlineThinkness, shapeCtx.fillColor
        );
    }

    void DrawHandle::DrawText(std::string_view text, const TextContext& textCtx) const
    {
        thread_local std::string buffer {text};
        buffer.assign(text.data(), text.size());

        rl::DrawTextPro(
            textCtx.font,
            text.data(),
            rl_cast(textCtx.position),
            rl_cast(textCtx.origin),
            textCtx.rotation.as_rad(),
            textCtx.fontSize,
            textCtx.spacing,
            textCtx.color
        );
    }

    void DrawHandle::DrawFPS(int posX, int posY) const { rl::DrawFPS(posX, posY); }

} // namespace dull::render
