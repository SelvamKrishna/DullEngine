#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/util/window_context.hpp"

#include <vendor/raylib.h>

namespace dull::core
{
    static inline App* sInstance = nullptr;
    static inline IProcessor* sProcessorPtr = nullptr;

    App::App() : zutil::Logger { { config::DULL_TAG, {"[APP]", zutil::ANSI::EX_Black} } }
    {
        zutil::Assert(sInstance == nullptr, "App can only be created once");
        sInstance = this;
    }

    App::~App() { App::_ShutdownSystems(); }

    [[nodiscard]] App& App::GetInstance() noexcept { return *sInstance; }
    [[nodiscard]] bool App::IsRunning()   noexcept { return sInstance->_isRunning; }

    void App::Init(const util::WindowContext& windowContext, IProcessor* processorPtr) noexcept
    {
        zutil::Assert(sInstance != nullptr, "App instance not yet created");

        int configFlags = {
            (windowContext.isVsyncEnabled ? rl::FLAG_VSYNC_HINT       : 0) |
            (windowContext.isResizeable   ? rl::FLAG_WINDOW_RESIZABLE : 0)
        };

        rl::SetConfigFlags(configFlags);
        rl::InitWindow(windowContext.dimension.x, windowContext.dimension.y, windowContext.title.c_str());
        rl::SetExitKey(rl::KEY_NULL);

        sInstance->Log(zutil::INFO, {"'{}' Opening", windowContext.title});

        App::_InitSystems(processorPtr);
    }

    void App::_InitSystems(IProcessor* processorPtr) noexcept
    {
        zutil::Assert(sInstance != nullptr, "App instance not yet created");
        sInstance->_isRunning = true;

        sProcessorPtr = (processorPtr != nullptr)
            ? processorPtr
            : static_cast<IProcessor*>(new _VoidProcessor {})
        ;

        sProcessorPtr->IInit();
    }

    void App::_ShutdownSystems() noexcept
    {
        sProcessorPtr->IShutdown();

        sInstance->Log(zutil::INFO, "Closing\n\n");

        rl::CloseWindow();
    }

    void App::Run() noexcept
    {
        sInstance->Log(zutil::INFO, "Running");

        while (!rl::WindowShouldClose() && sInstance->IsRunning()) [[likely]]
        {
            sProcessorPtr->IUpdate();
            if (sInstance->timeSystem._IsFixedProcess()) [[unlikely]] sProcessorPtr->IFixedUpdate();

            rl::BeginDrawing();
            rl::ClearBackground(rl::BLACK);
            sProcessorPtr->IDraw();
            rl::EndDrawing();
        }

        App::Quit();
    }

    void App::Quit() noexcept { sInstance->_isRunning = false; }

} // namespace dull::core
