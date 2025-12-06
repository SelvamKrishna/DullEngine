#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>
#include <vendor/zutils/zutils.hpp>

#include <format>
#include <string>

namespace dull::core {

static inline App* s_instance = nullptr;

App::App(const misc::AppContext& context)
{
    ZASSERT_EQ(s_instance, nullptr);
    s_instance = this;

    const std::string TITLE = (config::IS_DEBUG_BUILD)
    ? std::format("Dull Engine v{} - {}", config::getVerString(), context.title)
    : context.title;

    int flags = {
        (context.is_vsync      ? rl::FLAG_VSYNC_HINT       : 0) |
        (context.is_resizeable ? rl::FLAG_WINDOW_RESIZABLE : 0)
    };

    rl::SetConfigFlags(flags);
    rl::InitWindow(context.window_size.x, context.window_size.y, TITLE.c_str());
    rl::SetExitKey(rl::KEY_NULL);
    rl::SetTargetFPS(context.target_fps);

    _is_running = true;

    if constexpr (config::SHOULD_LOG_APP)
    {
        ZLOGI_IF(context.is_vsync)      << "App Init: V-Sync On";
        ZLOGI_IF(context.is_resizeable) << "App Init: Window made resizeable";
        ZLOGI << "App Initialized: " << TITLE << "\n";
    }
}

App::~App() noexcept
{
    ZLOGI_IF(config::SHOULD_LOG_APP) << "App Shutdown\n";
    if (_is_running) [[likely]] rl::CloseWindow();
}

[[nodiscard]] App& App::instance() noexcept { return *s_instance; }

void App::run() noexcept
{
    try {
        while (!rl::WindowShouldClose() && _is_running) [[likely]] {
        rl::BeginDrawing();
        rl::ClearBackground(rl::BLACK);
        rl::DrawFPS(10, 10);
        rl::EndDrawing();
        }
    }
    catch (const std::exception& ERR) {
        ZLOGE << "App Run (UNHANDLED): " << ERR.what();
    }
}

void App::logStats() const noexcept
{
    if constexpr (!config::IS_DEBUG_BUILD) return;

    ZLOGD << "Status -> App (" << (void*)s_instance << ")";
    ZLOG_V(_is_running);
}

} // namespace dull::core
