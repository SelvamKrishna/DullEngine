#include "engine/system/render_system.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

namespace dull::system {

void RenderSystem::_update() noexcept
{
    rl::BeginDrawing();
    rl::ClearBackground(rl::BLACK);

    ZON_DEBUG rl::DrawFPS(10, 10);

    for (const std::reference_wrapper<misc::IRenderCall>& RENDER_CALL : _permanent_render_calls)
        RENDER_CALL.get().iDraw();

    for (const std::reference_wrapper<misc::IRenderCall>& RENDER_CALL : _render_calls)
        RENDER_CALL.get().iDraw();

    _render_calls.clear();

    rl::EndDrawing();
}

void RenderSystem::reserve(size_t reserve) noexcept { _render_calls.reserve(reserve); }

void RenderSystem::addRenderCall(const std::reference_wrapper<misc::IRenderCall> render_call) noexcept
{
    (render_call.get().PERMANENT_CALL)
        ? _permanent_render_calls.emplace_back(render_call)
        : _render_calls.emplace_back(render_call);
}

void RenderSystem::removeRenderCall(const std::reference_wrapper<misc::IRenderCall> render_call) noexcept
{
    if (!render_call.get().PERMANENT_CALL) return;

    auto it = std::remove_if(
        _permanent_render_calls.begin(),
        _permanent_render_calls.end(),
        [&render_call](const std::reference_wrapper<misc::IRenderCall>& rc) {
            return &rc.get() == &render_call.get();
        }
    );

    _permanent_render_calls.erase(it, _permanent_render_calls.end());
}

} // namespace dull::system
