#include "engine/system/render_system.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

namespace dull::system {

std::vector<std::reference_wrapper<misc::IRenderCall>> RenderSystem::s_one_frame_call {};
std::vector<std::reference_wrapper<misc::IRenderCall>> RenderSystem::s_permanent_call {};

void RenderSystem::_update() noexcept
{
    rl::BeginDrawing();
    rl::ClearBackground(rl::BLACK);

    ZON_DEBUG rl::DrawFPS(10, 10);

    for (misc::IRenderCall& call: s_one_frame_call) call.iDraw();
    for (misc::IRenderCall& call: s_permanent_call) call.iDraw();

    rl::EndDrawing();
    s_one_frame_call.clear();
}

void RenderSystem::_quit() noexcept
{
    s_one_frame_call.clear();
    s_permanent_call.clear();
}

void RenderSystem::reserveOneFrameBuffer(size_t reserve) noexcept { s_one_frame_call.reserve(reserve); }
void RenderSystem::reservePermanentBuffer(size_t reserve) noexcept { s_permanent_call.reserve(reserve); }

void RenderSystem::addPermanentCall(misc::IRenderCall& render_call) noexcept
{
    s_permanent_call.emplace_back(render_call);
}

void RenderSystem::removePermanentCall(misc::IRenderCall& render_call) noexcept
{
    using RenderCallRef = std::reference_wrapper<misc::IRenderCall>;

    std::vector<RenderCallRef>::iterator it = std::remove_if(
        s_permanent_call.begin(),
        s_permanent_call.end(),
        [&render_call](RenderCallRef& call) { return &call.get() == &render_call; }
    );

    if (it != s_permanent_call.end()) s_permanent_call.erase(it, s_permanent_call.end());
}

void RenderSystem::addOneFrameCall(misc::IRenderCall& render_call) noexcept
{
    s_one_frame_call.emplace_back(render_call);
}

} // namespace dull::system
