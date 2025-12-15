#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

#include <format>
#include <string>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_APP)

[[nodiscard]]
AppContext AppContext::load() noexcept
{
    return AppContext {
        .title         = config::TITLE,
        .window_size   = config::WINDOW_SIZE,
        .is_vsync      = config::IS_VSYNC,
        .is_resizeable = config::IS_RESIZEABLE,
    };
}

void AppContext::logStats() const noexcept
{
    ZVAR(AppContext::title);
    ZVAR(AppContext::window_size.x);
    ZVAR(AppContext::window_size.y);
    ZVAR(AppContext::is_vsync);
    ZVAR(AppContext::is_resizeable);
}

static inline App* s_instance = nullptr;

App::App(const AppContext& context)
{
    ZPANIC_IF(s_instance != nullptr, "App can only be initialized once.");
    s_instance = this;

    const std::string TITLE = zlog::config::IS_MODE_DEBUG
    ? std::format("Dull Engine v{} - {}", config::getVerString(), context.title)
    : context.title;

    int flags = {
        (context.is_vsync      ? rl::FLAG_VSYNC_HINT       : 0) |
        (context.is_resizeable ? rl::FLAG_WINDOW_RESIZABLE : 0)
    };

    rl::SetConfigFlags(flags);
    rl::InitWindow(context.window_size.x, context.window_size.y, TITLE.c_str());
    rl::SetExitKey(rl::KEY_NULL);

    _is_running = true;
    _handle._init();

    _IF_LOG {
        context.logStats();
        ZINFO("App '{}' initialized", TITLE);
    }
}

App::~App() noexcept
{
    _IF_LOG ZINFO("App shutting down");
    if (_is_running) [[likely]] rl::CloseWindow();
}

[[nodiscard]]
App& App::instance() noexcept { return *s_instance; }

void App::run() noexcept
{
    _handle._setState(ProgramState::Process);

    constexpr double FIXED_PROCESS_INTERVAL = 1.0 / config::FIXED_PROCESS_FPS;
    double accumulated_time = 0.0f;

    _scene_sys._activate();

    try {
        while (!rl::WindowShouldClose() && _is_running) [[likely]] {
            /// TODO: Move to time system
            accumulated_time += rl::GetFrameTime();
            if (accumulated_time > FIXED_PROCESS_INTERVAL)
            {
                accumulated_time -= FIXED_PROCESS_INTERVAL;
                _scene_sys._fixedProcess();
            }

            _scene_sys._process();

            /// TODO: Move to render system
            rl::BeginDrawing();
            rl::ClearBackground(rl::BLACK);
            rl::DrawFPS(10, 10);
            rl::EndDrawing();
        }
    }
    catch (const std::exception& ERR) {
        ZERR("App (UNHANDLED): {}", ERR.what());
    }
}

#undef _IF_LOG

} // namespace dull::core
