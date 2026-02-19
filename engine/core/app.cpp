#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>

#include <format>
#include <string>

namespace dull::core {

static inline App* sInstance = nullptr;

App::App(const system::SystemContext& systemContext, const WindowContext& windowContext)
    : zutil::Logger { { config::DULL_TAG, {"[APP]", zutil::ANSI::EX_Black} } }
    , systems {systemContext}
{
    zutil::Assert(sInstance == nullptr, "App can only be created once");

    sInstance = this;

    int configFlags = {
        (windowContext.isVsyncEnabled ? rl::FLAG_VSYNC_HINT       : 0) |
        (windowContext.isResizeable   ? rl::FLAG_WINDOW_RESIZABLE : 0)
    };

    rl::SetConfigFlags(configFlags);
    rl::InitWindow(windowContext.dimension.x, windowContext.dimension.y, windowContext.title.c_str());
    rl::SetExitKey(rl::KEY_NULL);

    this->Log(zutil::INFO, {"'{}' Opening", windowContext.title});
}

App::~App() noexcept
{
    this->systems.processorRef.IShutdown();
    this->Log(zutil::INFO, "Closing\n\n");
    rl::CloseWindow();
}

[[nodiscard]] App& App::GetInstance() noexcept { return *sInstance; }

void App::Run() noexcept
{
    this->_isRunning = true;
    this->Log(zutil::INFO, "Running");

    this->systems.processorRef.IInit();

    while (!rl::WindowShouldClose() && this->IsRunning()) [[likely]]
    {
        this->systems.processorRef.IUpdate();

        if (this->systems.timeSystem._IsFixedProcess()) [[unlikely]]
            this->systems.processorRef.IFixedUpdate();

        rl::BeginDrawing();
        rl::ClearBackground(rl::BLACK);
        rl::DrawFPS(10, 10);
        rl::EndDrawing();
    }

    this->_isRunning = false;
}

void App::Quit() noexcept { this->_isRunning = false; }

} // namespace dull::core
