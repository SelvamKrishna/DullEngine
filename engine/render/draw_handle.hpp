#pragma once

#include "engine/core/render_system.hpp"
#include "engine/render/draw_context.hpp"
#include "engine/util/rect.hpp"

#include <zen/math/vec2.hpp>

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::render {

    struct DrawHandle {
        friend core::Engine;

    private:
        core::IRenderSystem& _refRenderSys;

        explicit DrawHandle(core::IRenderSystem& refRenderSys);
        ~DrawHandle();

    public:
        DrawHandle(DrawHandle&&)                 = delete;
        DrawHandle(const DrawHandle&)            = delete;
        DrawHandle& operator=(DrawHandle&&)      = delete;
        DrawHandle& operator=(const DrawHandle&) = delete;

        [[nodiscard]] const core::IRenderSystem& GetRenderSystem() const { return this->_refRenderSys; }

        void DrawRectangle(
            const util::Rect& rectangle,
            zen::angle rotation = zen::angle::from_deg(0),
            const ShapeContext& ctxShape = {}
        ) const;

        void DrawCircle(
            const zen::vec2& position,
            float radius,
            const ShapeContext& ctxShape = {}
        ) const;

        void DrawLine(
            const zen::vec2& pointA,
            const zen::vec2& pointB,
            const ShapeContext& ctxShape = {}
        ) const;

        #warning "TODO: `rl::Font` wrapper class"
        void DrawText(std::string_view text, const TextContext& ctxText = {}) const;

        void DrawFPS(int posX, int posY) const;
    };

} // namespace dull::render
