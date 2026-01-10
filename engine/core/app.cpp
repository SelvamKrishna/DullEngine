#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

#include <format>
#include <string>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_APP)

void AppContext::logStats() const noexcept
{
    ZTRC_S("Logging AppContext");
    ZVAR(title);
    ZVAR(window_size.x);
    ZVAR(window_size.y);
    ZVAR(is_vsync);
    ZVAR(is_resizeable);
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

    _handle._setState(ProgramState::Initialization);

    _IF_LOG {
        context.logStats();
        ZINFO("App '{}' initialized", TITLE);
    }

    DULL_CTX.audio_sys._init();
}

App::~App() noexcept
{
    _IF_LOG ZINFO("App shutting down");
    if (_handle.isRunning()) [[likely]] rl::CloseWindow();
}

[[nodiscard]]
App& App::instance() noexcept { return *s_instance; }

void App::run() noexcept
{
    _handle._setState(ProgramState::Processing);

    _IF_LOG ZINFO("App running");

    _processor.iStart();

    try {
        while (!rl::WindowShouldClose() && _handle.isRunning()) [[likely]] {
            DULL_CTX.audio_sys._update();

            if (_time_sys._isFixedProcess()) _processor.iFixedProcess();
            _processor.iProcess();

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

void App::quit() noexcept { _handle._setState(ProgramState::ShuttingDown); }

#undef _IF_LOG

} // namespace dull::core
