#include "engine/config.hpp"
#include "engine/core/engine.hpp"
#include "engine/core/processor.hpp"
#include "engine/render/draw_handle.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"

#include <vendor/raylib.h>
#include <vendor/zenutil/zen_prelude.hpp>

namespace dull::core {

    static inline Engine* sInstance = nullptr;
    static inline IProcessor* sProcessorPtr = nullptr;

    Engine::Engine() : zen::core::Logger { { config::DULL_TAG, {"[APP]", zen::core::ANSI::EX_Black} } }
    {
        zen::core::Assert(sInstance == nullptr, "Engine can only be created once");
        sInstance = this;
    }

    Engine::~Engine() { Engine::_ShutdownSystems(); }

    [[nodiscard]] Engine& Engine::GetInstance() noexcept { return *sInstance; }
    [[nodiscard]] bool Engine::IsRunning() noexcept { return sInstance->_isRunning; }

    void Engine::Init(const util::WindowContext& windowContext) noexcept
    {
        zen::core::Assert(sInstance != nullptr, "Engine instance not yet created");

        int configFlags = {
            (windowContext.isVsync ? rl::FLAG_VSYNC_HINT       : 0) |
            (windowContext.isResizeable   ? rl::FLAG_WINDOW_RESIZABLE : 0)
        };

        rl::SetConfigFlags(configFlags);
        rl::InitWindow(windowContext.dimension.x, windowContext.dimension.y, windowContext.title.c_str());
        rl::SetExitKey(rl::KEY_NULL);

        sInstance->Log(zen::core::INFO, {"'{}' Opening", windowContext.title});
    }

    void Engine::_InitSystems(const util::ProcessContext& processContext) noexcept
    {
        zen::core::Assert(sInstance != nullptr, "Engine instance not yet created");
        sInstance->_isRunning = true;

        sProcessorPtr = (processContext.processorPtr != nullptr)
            ? processContext.processorPtr
            : static_cast<IProcessor*>(new _VoidProcessor {})
        ;

        sProcessorPtr->IInit();
    }

    void Engine::_ShutdownSystems() noexcept
    {
        sProcessorPtr->IShutdown();
        sInstance->Log(zen::core::INFO, "Closing\n\n");
        rl::CloseWindow();
    }

    void Engine::Run(const util::ProcessContext& processContext) noexcept
    {
        Engine::_InitSystems(processContext);
        sInstance->Log(zen::core::INFO, "Running");

        while (!rl::WindowShouldClose() && sInstance->IsRunning()) [[likely]]
        {
            sInstance->timeSystem._UpdateDeltaTime(rl::GetFrameTime());
            sProcessorPtr->IUpdate();

            while (sInstance->timeSystem._TryConsumeAccumulated())
            {
                sProcessorPtr->IFixedUpdate();
                Z_TODO("Physics Logic goes here");
            }

            render::DrawHandle drawHandle;
            sProcessorPtr->IDraw(drawHandle);
        }

        Engine::Quit();
    }

    void Engine::Quit() noexcept { sInstance->_isRunning = false; }

} // namespace dull::core
