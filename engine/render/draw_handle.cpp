#include "engine/render/draw_handle.hpp"

#include <vendor/raylib.h>
#include <vendor/zenutil/zen_prelude.hpp>

namespace dull::render {

    DrawHandle::DrawHandle()
    {
        rl::BeginDrawing();
        rl::ClearBackground(rl::BLACK);
        Z_ON_DBG { rl::DrawFPS(10, 10); }
    }

    DrawHandle::~DrawHandle() { rl::EndDrawing(); }

    const util::Transform2D& DrawHandle::_GetValidTransform(const util::Transform2D* transformPtr) noexcept
    {
        return transformPtr == nullptr ? util::DEFAULT_TRANSFORM_2D : *transformPtr;
    }

    void DrawHandle::DrawRectangle(const util::Rect& rectangle, const DrawContext& drawContext) const
    {
        const auto& TRANSFORM = DrawHandle::_GetValidTransform(drawContext.TRANSFORM_PTR);

        rl::DrawRectanglePro(
            util::Rect {
                TRANSFORM.position + drawContext.TRANSFORM_PTR->position,
                rectangle.GetDimension() * TRANSFORM.scale
            },
            (util::Vec2f) (rectangle.GetDimension() * 0.5f),
            TRANSFORM.rotation.AsDegrees(),
            drawContext.tintOverlay
        );
    }

    void DrawHandle::DrawCircle(float radius, const util::Vec2f& position, const util::Color& color, float scale) const
    {
        rl::DrawCircleV(position, radius * scale, color);
    }

} // namespace dull::render
