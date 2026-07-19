#include "engine/render/draw_handle.hpp"
#include "engine/util/adapter.hpp"

#include <zen/log.hpp>
#include <zen/math/vec2.hpp>

#include <vendor/raylib.h>

namespace dull::render {

    DrawHandle::DrawHandle()
    {
        rl::BeginDrawing();
        rl::ClearBackground(rl::RL_BLACK);
    }

    DrawHandle::~DrawHandle()
    {
        rl::DrawFPS(10, 10);
        rl::EndDrawing();
    }

    void DrawHandle::DrawRectangle(
        const util::Rect& rectangle,
        zen::angle rotation,
        const ShapeContext& shapeContext
    ) const
    {
        rl::DrawRectanglePro(
            rectangle,
            rl_cast(rectangle.GetDimension() * 0.5f),
            rotation.as_deg(),
            shapeContext.fillColor
        );

        if (!shapeContext.HasOutline()) return;
        rl::DrawRectangleLinesEx(rectangle, shapeContext.outlineThinkness, shapeContext.outlineColor);
    }

    void DrawHandle::DrawCircle(
        const zen::vec2& position,
        float radius,
        const ShapeContext& shapeContext
    ) const
    {
        if (shapeContext.HasOutline()) rl::DrawCircleV(
            rl_cast(position), radius + shapeContext.outlineThinkness, shapeContext.outlineColor
        );

        rl::DrawCircleV(rl_cast(position), radius, shapeContext.fillColor);
    }

    void DrawHandle::DrawLine(
        const zen::vec2& pointA,
        const zen::vec2& pointB,
        const ShapeContext& shapeContext
    ) const
    {
        rl::DrawLineEx(
            rl_cast(pointA), rl_cast(pointB),
            shapeContext.outlineThinkness, shapeContext.fillColor
        );
    }

} // namespace dull::render
