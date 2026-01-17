#include "engine/system/render_system.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

namespace dull::system {

void RenderSystem::_update() noexcept
{
    rl::BeginDrawing();
    rl::ClearBackground(rl::BLACK);
    ZON_DEBUG rl::DrawFPS(10, 10);
    rl::EndDrawing();

    for (const std::reference_wrapper<misc::IRenderCall>& RENDER_CALL : _render_calls)
        RENDER_CALL.get().iDraw();

    _render_calls.clear();
}

void RenderSystem::reserve(size_t reserve) noexcept { _render_calls.reserve(reserve); }

void RenderSystem::addRenderCall(const std::reference_wrapper<misc::IRenderCall> render_call) noexcept
{
    _render_calls.emplace_back(render_call);
}

} // namespace dull::system
