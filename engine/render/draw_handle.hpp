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

        void DrawRectangle(const util::Rect& rectangle, const DrawContext& = DEFAULT_DRAW_CONTEXT) const;
        void DrawCircle(float radius, const util::Vec2f& position, const util::Color& color = DEFAULT_COLOR, float scale = 1.0F) const;
    };

} // namespace dull::render
