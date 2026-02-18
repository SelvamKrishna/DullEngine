#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>

#include <format>
#include <string>

#include "engine/component/timer.hpp" // test

namespace dull::core {

static inline App* sInstance = nullptr;

App::App(const AppContext& context) : zutil::Logger {
    {
        config::DULL_TAG,
        {"[APP]", zutil::ANSI::EX_Black}
    }
}
{
    zutil::Assert(sInstance == nullptr, "App can only be created once");

    sInstance = this;

    int configFlags = {
        (context.isVsyncEnabled ? rl::FLAG_VSYNC_HINT       : 0) |
        (context.isResizeable   ? rl::FLAG_WINDOW_RESIZABLE : 0)
    };

    rl::SetConfigFlags(configFlags);
    rl::InitWindow(context.windowDimension.x, context.windowDimension.y, context.title.c_str());
    rl::SetExitKey(rl::KEY_NULL);

    this->_handle._SetState(ProgramState::Opening);
    this->Log(zutil::INFO, {"'{}' Opening", context.title});
}

App::~App() noexcept { this->Quit(); }

[[nodiscard]] App& App::GetInstance() noexcept { return *sInstance; }

void App::Run() noexcept
{
    this->_handle._SetState(ProgramState::Running);
    this->Log(zutil::INFO, "Running");

    // Start();
    component::Timer timer { 5 }; // test

    while (!rl::WindowShouldClose() && this->_handle.IsRunning()) [[likely]]
    {
        try
        {
            if (this->_timeSystem._IsFixedProcess()) [[unlikely]] { /* FixedProcess(); */ }
            // Process();

            if (!timer.IsActive()) timer.Start(); // test
            if (timer.IsOver()) { this->Log(zutil::DBG, "Timer testing"); } // test

            rl::ClearBackground(rl::BLACK);
            rl::BeginDrawing();
            rl::DrawText("Hello", 100, 100, 24, rl::WHITE);
            rl::EndDrawing();
        }
        catch (const std::exception& ERR)
        {
            this->Log(zutil::ERR, {"Unhandled: {}", ERR.what()});
            break;
        }
    }

    this->Quit();
}

void App::Quit() noexcept
{
    if (this->_handle.IsClosing()) [[unlikely]] return;

    this->_handle._SetState(ProgramState::Closing);
    this->Log(zutil::INFO, "Closing\n\n");

    rl::CloseWindow();
}

} // namespace dull::core
