#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>
#include <vendor/zutils/log.hpp>
#include <vendor/zutils/test.hpp>
#include <vendor/zutils/tools.hpp>

#include <format>
#include <string>

namespace dull::core {

[[nodiscard]]
AppContext AppContext::load() noexcept
{
    ZTODO("Load AppContext from config file");
    return {};
}

static inline App* s_instance = nullptr;

App::App(const AppContext& context)
{
    ZASSERT_EQ(s_instance, nullptr);
    s_instance = this;

    const std::string TITLE = zutils::config::IS_MODE_DEBUG
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
    _handle._init();

    if constexpr (config::SHOULD_LOG_APP)
    {
        ZINFO_IF(context.is_vsync, "App Init: V-Sync On");
        ZINFO_IF(context.is_resizeable, "App Init: Window made resizeable");
        ZINFO("App Initialized: {}", TITLE);
    }
}

App::~App() noexcept
{
    ZINFO_IF(config::SHOULD_LOG_APP, "App Shutdown\n");
    if (_is_running) [[likely]] rl::CloseWindow();
}

[[nodiscard]]
App& App::instance() noexcept { return *s_instance; }

void App::run() noexcept
{
    constexpr double FIXED_PROCESS_INTERVAL = 1.0 / config::FIXED_PROCESS_FPS;
    double accumulated_time = 0.0f;

    try {
        while (!rl::WindowShouldClose() && _is_running) [[likely]] {
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
        ZERR("App Run (UNHANDLED): {}", ERR.what());
    }
}

void App::logStats() const noexcept
{
    ZON_RELEASE return;
    ZDBG("Status -> App ({})", (void*)s_instance);
    ZVAR(_is_running);
}

} // namespace dull::core
