#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>
#include <vendor/zlog_v2.hpp>

#include <format>
#include <string>

namespace dull::core {

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

    if constexpr (config::SHOULD_LOG_APP) {
        context.logStats();
        ZINFO("App '{}' initialized", TITLE);
    }

    _audio_sys._init();
}

App::~App() noexcept
{
    if (_handle.isRunning()) [[likely]] rl::CloseWindow();
    quit();
    if constexpr (config::SHOULD_LOG_APP) ZINFO("App shutting down");
}

[[nodiscard]]
App& App::instance() noexcept { return *s_instance; }

void App::run() noexcept
{
    _handle._setState(ProgramState::Processing);

    if constexpr (config::SHOULD_LOG_APP) ZINFO("App running");

    _processor.iStart();

    try {
        while (!rl::WindowShouldClose() && _handle.isRunning()) [[likely]]
        {
            if (_time_sys._isFixedProcess()) [[unlikely]] _processor.iFixedProcess();
            _processor.iProcess();

            _audio_sys._update();
            _render_sys._update();
        }
    }
    catch (const std::exception& ERR) {
        ZERR("App (UNHANDLED): {}", ERR.what());
    }
}

void App::quit() noexcept
{
    _handle._setState(ProgramState::ShuttingDown);
    _audio_sys._quit();
}

#undef _IF_LOG

} // namespace dull::core
