#include "engine/core/engine.hpp"
#include "engine/core/processor.hpp"
#include "engine/render/draw_handle.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"

#include <zen/log.hpp>
#include <vendor/raylib.h>

namespace dull::core {

    static inline Engine*     sInstance     {nullptr};
    static inline IProcessor* sProcessorPtr {nullptr};

    Engine::Engine()
    {
        zen::ansi_gaurd _logOSGaurd {std::cout};
        zen::ansi_gaurd _errOSGaurd {std::cerr};

        // zen::assert(sInstance == nullptr, "Engine can only be created once");
        sInstance = this;
    }

    Engine::~Engine() { Engine::_ShutdownSystems(); }

    [[nodiscard]] Engine& Engine::GetInstance() noexcept { return *sInstance; }
    [[nodiscard]] bool Engine::IsRunning() noexcept { return sInstance->_isRunning; }

    void Engine::Init(const util::WindowContext& windowContext) noexcept
    {
        // zen::assert(sInstance != nullptr, "Engine instance not yet created");

        int configFlags {
            (windowContext.isVsync      ? rl::FLAG_VSYNC_HINT       : 0) |
            (windowContext.isResizeable ? rl::FLAG_WINDOW_RESIZABLE : 0)
        };

        const int32_t WINDOW_WIDTH  = windowContext.dimension.first;
        const int32_t WINDOW_HEIGHT = windowContext.dimension.second;

        rl::SetConfigFlags(configFlags);
        rl::InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowContext.title.c_str());
        rl::SetExitKey(rl::KEY_NULL);

        // zen::info() << sInstance->_logTag << "Opening " << windowContext.title;
    }

    void Engine::_InitSystems(const util::ProcessContext& processContext) noexcept
    {
        // zen::assert(sInstance != nullptr, "Engine instance not yet created");
        sInstance->_isRunning = true;

        sProcessorPtr = (processContext.processorPtr != nullptr)
            ? processContext.processorPtr
            : static_cast<IProcessor*>(new DirectProcessor { {} })
        ;

        sProcessorPtr->IInit();
    }

    void Engine::_ShutdownSystems() noexcept
    {
        sProcessorPtr->IShutdown();
        // sInstance->Log(zen::core::INFO, "Closing\n\n");
        rl::CloseWindow();
    }

    void Engine::Run(const util::ProcessContext& processContext) noexcept
    {
        Engine::_InitSystems(processContext);
        // sInstance->Log(zen::core::INFO, "Running");

        util::GlobalAccessor globalAccessor {
            .timeRef  = sInstance->timeSystem,
            .audioRef = sInstance->audioSystem
        };

        while (!rl::WindowShouldClose() && sInstance->IsRunning()) [[likely]]
        {
            sInstance->timeSystem._UpdateDeltaTime(rl::GetFrameTime());
            sProcessorPtr->IUpdate(globalAccessor);

            while (sInstance->timeSystem._TryConsumeAccumulated())
            {
                sProcessorPtr->IFixedUpdate(globalAccessor);
                // Z_TODO("Physics Logic goes here");
            }

            render::DrawHandle drawHandle;
            sProcessorPtr->IDraw(drawHandle);
        }
    }

    void Engine::Quit() noexcept { sInstance->_isRunning = false; }

} // namespace dull::core
