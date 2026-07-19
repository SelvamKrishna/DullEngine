#pragma once

#include "engine/render/draw_context.hpp"
#include "engine/util/rect.hpp"

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::render {

    struct DrawHandle {
        friend core::Engine;

    private:
        explicit DrawHandle();
        ~DrawHandle();

        [[nodiscard]]
        static const util::Transform2D& _GetValidTransform(const util::Transform2D* transformPtr) noexcept;

        static constexpr util::Color DEFAULT_COLOR = util::Color::White();

    public:
        DrawHandle(DrawHandle&&)                 = delete;
        DrawHandle(const DrawHandle&)            = delete;
        DrawHandle& operator=(DrawHandle&&)      = delete;
        DrawHandle& operator=(const DrawHandle&) = delete;

        void DrawRectangle(
            const util::Rect& rectangle,
            zen::angle rotation = zen::angle::from_deg(0),
            const ShapeContext& shapeContext = DEFAULT_SHAPE_CONTEXT
        ) const;

        void DrawCircle(
            const zen::vec2& position,
            float radius,
            const ShapeContext& shapeContext = DEFAULT_SHAPE_CONTEXT
        ) const;

        void DrawLine(
            const zen::vec2& pointA,
            const zen::vec2& pointB,
            const ShapeContext& shapeContext = DEFAULT_SHAPE_CONTEXT
        ) const;
    };

} // namespace dull::render
