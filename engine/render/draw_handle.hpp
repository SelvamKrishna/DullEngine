#pragma once

#include "engine/render/renderer.hpp"
#include "engine/render/draw_context.hpp"
#include "engine/util/rect.hpp"

#include <zen/math/vec2.hpp>

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::render {

    struct DrawHandle {
        friend core::Engine;

    private:
        IRenderer& _refRenderer;

        explicit DrawHandle(IRenderer& refRenderer);
        ~DrawHandle();

    public:
        DrawHandle(DrawHandle&&)                 = delete;
        DrawHandle(const DrawHandle&)            = delete;
        DrawHandle& operator=(DrawHandle&&)      = delete;
        DrawHandle& operator=(const DrawHandle&) = delete;

        [[nodiscard]] const IRenderer& GetRenderer() const { return this->_refRenderer; }

        void DrawRectangle(
            const util::Rect& rectangle,
            const DrawContext& ctxDraw = {},
            const ShapeContext& ctxShape = {}
        ) const;

        void DrawCircle(
            const DrawContext& ctxDraw = {},
            const ShapeContext& ctxShape = {}
        ) const;

        void DrawLine(
            const zen::vec2& pointA,
            const zen::vec2& pointB,
            const ShapeContext& ctxShape = {}
        ) const;

        #warning "TODO: `rl::Font` wrapper class"
        void DrawText(
            std::string_view text,
            const DrawContext& ctxDraw = {},
            const TextContext& ctxText = {}
        ) const;

        void DrawFPS(int posX, int posY) const;
    };

} // namespace dull::render
