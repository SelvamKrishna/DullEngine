#include "engine/core/engine.hpp"
#include "engine/core/processor.hpp"
#include "engine/render/draw_handle.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"

#include <zen/log.hpp>
#include <vendor/raylib.h>

namespace dull::core {

    const zen::log_tag Engine::_LOG {"APP", zen::ansi_color::BLUE, &config::DULL_TAG};

    Engine::~Engine()
    {
        if (Engine::IsRunning() || Engine::IsInitialized()) Engine::_ShutdownSystems();
    }

    [[nodiscard]] Engine& Engine::GetInstance() noexcept
    {
        static Engine instance;
        return instance;
    }

    void Engine::_InitWindow(const util::WindowContext&& windowContext) noexcept
    {
        zen::log_process process {"Initializing Window", &Engine::_LOG};

        rl::SetConfigFlags(static_cast<unsigned int>(
            (windowContext.isVsync      ? rl::FLAG_VSYNC_HINT       : 0) |
            (windowContext.isResizeable ? rl::FLAG_WINDOW_RESIZABLE : 0)
        ));

        rl::InitWindow(windowContext.dimension[0], windowContext.dimension[1], windowContext.title.c_str());
        rl::SetExitKey(rl::KEY_NULL);

        process.log_panic_if(!rl::IsWindowReady(), "Initialization Failed");
    }

    void Engine::Init(const util::WindowContext&& windowContext) noexcept
    {
        rl::SetTraceLogCallback(util::_RLTraceLogCallBack);

        zen::log_process process {"Initializing Engine", &Engine::_LOG};
        Engine& inst {DULL_INST};

        if (Engine::IsInitialized())
            return process.log_fallback("Engine Already Initialized");

        inst._InitWindow(std::move(windowContext));
        inst._windowContext = std::make_unique<util::WindowContext>(windowContext);
        inst._isInitialized = true;

        process.log_success();
    }

    void Engine::_InitSystems(const util::ProcessContext&& processContext) noexcept
    {
        zen::log_process process {"Initializing Systems", &Engine::_LOG};
        Engine& inst {DULL_INST};

        process.log_panic_if(Engine::IsRunning(), "Engine Is Already Running");
        inst._processContext = std::make_unique<util::ProcessContext>();

        inst._processContext->processorPtr = (processContext.processorPtr == nullptr)
            ? new core::DirectProcessor {}
            : processContext.processorPtr;

        inst._isRunning = true;
        inst._processContext->processorPtr->IInit();

        process.log_success();
    }

    void Engine::_ShutdownSystems() noexcept
    {
        zen::log_process process {"Shutting Down Systems", &Engine::_LOG};
        Engine& inst {DULL_INST};

        if (!Engine::IsRunning() && !Engine::IsInitialized()) return;

        inst._processContext->processorPtr->IShutdown();

        if (rl::IsWindowReady()) rl::CloseWindow();

        inst._isRunning = false;
        inst._isInitialized = false;
        process.log_success();
    }

    void Engine::Run(util::ProcessContext processContext) noexcept
    {
        zen::log_process process {"Running Application", &Engine::_LOG};
        Engine& inst {DULL_INST};
        system::TimeSystem& timeSystem = inst.timeSys;
        system::AudioSystem& audioSystem = inst.audioSys;

        process.log_panic_if(!Engine::IsInitialized(), "Engine Un-Initialized");
        Engine::_InitSystems(std::move(processContext));
        process.log_panic_if(!Engine::IsRunning(), "Engine Not Running");

        util::GlobalAccessor globalAccessor {
            .refWindow {inst.window},
            .refTime   {timeSystem},
            .refAudio  {audioSystem},
        };

        Engine::_LOG.info() << "Running Application...";
        while (!rl::WindowShouldClose() && inst.IsRunning()) [[likely]]
        {
            timeSystem._Update(rl::GetFrameTime());
            inst._processContext->processorPtr->IUpdate(globalAccessor);

            while (timeSystem._ShouldFixedUpdate())
            {
                inst._processContext->processorPtr->IFixedUpdate(globalAccessor);
                #warning "TODO: Physics logic goes here"
            }

            render::DrawHandle drawHandle {};
            inst._processContext->processorPtr->IDraw(drawHandle);
        }

        inst._ShutdownSystems();
        process.log_success();
    }

    void Engine::Quit() noexcept
    {
        Engine& inst {DULL_INST};
        if (!inst._isRunning) return;

        inst._isRunning = false;
        Engine::_LOG.info() << "Quit Requested\n";
    }

} // namespace dull::core
