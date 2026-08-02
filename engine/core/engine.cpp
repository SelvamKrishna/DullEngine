#include "engine/core/engine.hpp"
#include "engine/core/processor.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"
#include "engine/render/draw_handle.hpp"

#include <zen/log.hpp>
#include <vendor/raylib.h>

namespace dull::core {

    static inline Engine*     sInstance     {nullptr};
    static inline IProcessor* sProcessorPtr {nullptr};

    Engine::Engine()
    {
        static const zen::ansi_gaurd _OUT_GAURD {std::cout};
        static const zen::ansi_gaurd _ERR_GAURD {std::cerr};

        zen::assert(sInstance == nullptr, "Engine can only be created once");
        sInstance = this;
    }

    [[nodiscard]] Engine& Engine::GetInstance() noexcept { return *sInstance; }
    [[nodiscard]] bool Engine::IsRunning() noexcept { return sInstance->_isRunning; }

    void Engine::Init(const util::WindowContext& windowContext) noexcept
    {
        if (sInstance != nullptr) { return; }

        static Engine _engine;
        sInstance = &_engine;

        int configFlags {
            (windowContext.isVsync      ? rl::FLAG_VSYNC_HINT       : 0) |
            (windowContext.isResizeable ? rl::FLAG_WINDOW_RESIZABLE : 0)
        };

        const int32_t WINDOW_WIDTH  = windowContext.dimension.first;
        const int32_t WINDOW_HEIGHT = windowContext.dimension.second;

        rl::SetConfigFlags(configFlags);
        rl::InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, windowContext.title.c_str());
        rl::SetExitKey(rl::KEY_NULL);

        Engine::_LOG.info() << "Opening " << windowContext.title;
    }

    void Engine::_InitSystems(const util::ProcessContext& processContext) noexcept
    {
        zen::assert(rl::IsWindowReady(), "Window is not ready", Engine::_LOG);
        zen::assert(sInstance != nullptr, "Engine instance not yet created", Engine::_LOG);
        zen::assert(sInstance->_isRunning == false, "Engine is already running", Engine::_LOG);

        sInstance->_isRunning = true;
        sProcessorPtr = (processContext.processorPtr == nullptr)
            ? new DirectProcessor { {} }
            : processContext.processorPtr;

        sProcessorPtr->IInit();
    }

    void Engine::_ShutdownSystems() noexcept
    {
        Engine::_LOG.info() << "Exiting...\n";
        rl::CloseWindow();
        sProcessorPtr->IShutdown();
    }

    void Engine::Run(util::ProcessContext processContext) noexcept
    {
        Engine::_InitSystems(processContext);
        Engine::_LOG.info() << "Running";

        util::GlobalAccessor globalAccessor {
            .WINDOW_SIZE {rl::GetScreenWidth(), rl::GetScreenHeight()},
            .timeRef  {sInstance->timeSystem},
            .audioRef {sInstance->audioSystem},
        };

        while (!rl::WindowShouldClose() && sInstance->IsRunning()) [[likely]]
        {
            sInstance->timeSystem._UpdateDeltaTime(rl::GetFrameTime());
            sProcessorPtr->IUpdate(globalAccessor);

            while (sInstance->timeSystem._TryConsumeAccumulated())
            {
                sProcessorPtr->IFixedUpdate(globalAccessor);
                #warning "Physics Logic goes here"
            }

            render::DrawHandle drawHandle {};
            sProcessorPtr->IDraw(drawHandle);
        }

        Engine::_ShutdownSystems();
    }

    void Engine::Quit() noexcept { sInstance->_isRunning = false; }

} // namespace dull::core
