#include "engine/render/draw_handle.hpp"
#include "engine/util/adapter.hpp"

#include <zen/log.hpp>
#include <zen/math/vec2.hpp>

#include <vendor/raylib.h>

namespace dull::render {

    DrawHandle::DrawHandle(IRenderer& refRenderer) : _refRenderer {refRenderer}
    { rl::BeginDrawing(); rl::ClearBackground(color::BLACK); }

    DrawHandle::~DrawHandle() { rl::EndDrawing(); }

    void DrawHandle::DrawRectangle(
        const util::Rect& rectangle,
        const DrawContext& ctxDraw,
        const ShapeContext& ctxShape
    ) const {
        util::Rect rectangleModified {rectangle};
        rectangleModified.Move(ctxDraw.transform.position);
        rectangleModified.Scale(ctxDraw.transform.scale);

        rl::DrawRectanglePro(
            rectangleModified,
            rl_cast(rectangleModified.GetDimension() * 0.5f),
            ctxDraw.transform.rotation.as_deg(),
            ctxShape.fillColor
        );

        if (ctxShape.HasOutline()) rl::DrawRectangleLinesEx(
            rectangle, ctxShape.outlineThinkness, ctxShape.outlineColor
        );
    }

    void DrawHandle::DrawCircle(
        const DrawContext& ctxDraw,
        const ShapeContext& ctxShape
    ) const
    {
        if (ctxShape.HasOutline()) rl::DrawCircleV(
            rl_cast(ctxDraw.transform.position),
            ctxDraw.transform.GetScaleUnit() + ctxShape.outlineThinkness,
            ctxShape.outlineColor
        );

        rl::DrawCircleV(rl_cast(ctxDraw.transform.position), ctxDraw.transform.GetScaleUnit(), ctxShape.fillColor);
    }

    void DrawHandle::DrawLine(
        const zen::vec2& pointA,
        const zen::vec2& pointB,
        const ShapeContext& ctxShape
    ) const
    {
        rl::DrawLineEx(
            rl_cast(pointA), rl_cast(pointB),
            ctxShape.outlineThinkness, ctxShape.fillColor
        );
    }

    void DrawHandle::DrawText(std::string_view text, const DrawContext& ctxDraw, const TextContext& ctxText) const
    {
        thread_local std::string buffer {text};
        buffer.assign(text.data(), text.size());

        rl::DrawTextPro(
            ctxText.font,
            text.data(),
            rl_cast(ctxDraw.transform.position),
            rl_cast(ctxText.origin),
            ctxDraw.transform.rotation.as_rad(),
            ctxDraw.transform.GetScaleUnit(),
            ctxText.spacing,
            ctxDraw.tintOverlay
        );
    }

    void DrawHandle::DrawFPS(int posX, int posY) const { rl::DrawFPS(posX, posY); }

} // namespace dull::render
