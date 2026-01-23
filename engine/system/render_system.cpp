#include "engine/system/render_system.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

namespace dull::system {

void RenderSystem::_update() noexcept
{
    rl::BeginDrawing();
    rl::ClearBackground(rl::BLACK);

    ZON_DEBUG rl::DrawFPS(10, 10);

    for (misc::IRenderCall& call: _one_frame_call) call.iDraw();
    for (misc::IRenderCall& call: _permanent_call) call.iDraw();

    rl::EndDrawing();
    _one_frame_call.clear();
}

void RenderSystem::reserveOneFrameBuffer(size_t reserve) noexcept { _one_frame_call.reserve(reserve); }
void RenderSystem::reservePermanentBuffer(size_t reserve) noexcept { _permanent_call.reserve(reserve); }

void RenderSystem::addPermanentCall(misc::IRenderCall& render_call) noexcept
{
    _permanent_call.emplace_back(render_call);
}

void RenderSystem::removePermanentCall(misc::IRenderCall& render_call) noexcept
{
    using RenderCallRef = std::reference_wrapper<misc::IRenderCall>;

    std::vector<RenderCallRef>::iterator it = std::remove_if(
        _permanent_call.begin(),
        _permanent_call.end(),
        [&render_call](RenderCallRef& call) { return &call.get() == &render_call; }
    );

    _permanent_call.erase(it);
}

void RenderSystem::addOneFrameCall(misc::IRenderCall& render_call) noexcept
{
    _one_frame_call.emplace_back(render_call);
}

} // namespace dull::system
