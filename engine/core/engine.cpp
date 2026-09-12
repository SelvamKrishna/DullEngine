#include "engine/core/engine.hpp"
#include "engine/core/processor.hpp"
#include "engine/core/time_system.hpp"
#include "engine/core/audio_system.hpp"
#include "engine/render/draw_handle.hpp"

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

    void Engine::_InitWindow(const util::WindowContext&& ctxWindow) noexcept
    {
        zen::log_process process {"Initializing Window", &Engine::_LOG};

        rl::SetConfigFlags(static_cast<unsigned int>(
            (ctxWindow.isVsync      ? rl::FLAG_VSYNC_HINT       : 0) |
            (ctxWindow.isResizeable ? rl::FLAG_WINDOW_RESIZABLE : 0)
        ));

        rl::InitWindow(ctxWindow.dimension[0], ctxWindow.dimension[1], ctxWindow.title.c_str());
        rl::SetExitKey(rl::KEY_NULL);

        process.log_panic_if(!rl::IsWindowReady(), "Initialization Failed");
    }

    void Engine::Init(const util::WindowContext&& ctxWindow) noexcept
    {
        rl::SetTraceLogCallback(util::_RLTraceLogCallBack);

        zen::log_process process {"Initializing Engine", &Engine::_LOG};
        Engine& inst {DULL_INST};

        if (Engine::IsInitialized())
            return process.log_fallback("Engine Already Initialized");

        inst._InitWindow(std::move(ctxWindow));
        inst._ctxWindow = std::make_unique<util::WindowContext>(ctxWindow);
        inst._isInitialized = true;

        process.log_success();
    }

    void Engine::_InitSystems(const util::ProcessContext&& ctxProcess) noexcept
    {
        zen::log_process process {"Initializing Systems", &Engine::_LOG};
        Engine& inst {DULL_INST};

        process.log_panic_if(Engine::IsRunning(), "Engine Is Already Running");
        inst._ctxProcess = std::make_unique<util::ProcessContext>();

        inst._ctxProcess->ptrProcessor = (ctxProcess.ptrProcessor == nullptr)
            ? new DirectProcessor {}
            : ctxProcess.ptrProcessor;

        inst._ctxProcess->ptrRenderSys = (ctxProcess.ptrRenderSys == nullptr)
            ? new render::IRenderer {}
            : ctxProcess.ptrRenderSys;

        inst._isRunning = true;
        inst._ctxProcess->ptrProcessor->IInit();
        inst._ctxProcess->ptrRenderSys->IInit();

        process.log_success();
    }

    void Engine::_ShutdownSystems() noexcept
    {
        zen::log_process process {"Shutting Down Systems", &Engine::_LOG};
        Engine& inst {DULL_INST};

        if (!Engine::IsRunning() && !Engine::IsInitialized()) return;

        inst._ctxProcess->ptrProcessor->IShutdown();
        inst._ctxProcess->ptrRenderSys->IShutdown();

        if (rl::IsWindowReady()) rl::CloseWindow();

        inst._isRunning = false;
        inst._isInitialized = false;
        process.log_success();
    }

    void Engine::Run(util::ProcessContext ctxProcess) noexcept
    {
        zen::log_process process {"Running Application", &Engine::_LOG};
        Engine& inst {DULL_INST};
        TimeSystem& timeSystem {inst.timeSys};
        AudioSystem& audioSystem {inst.audioSys};

        process.log_panic_if(!Engine::IsInitialized(), "Engine Un-Initialized");
        Engine::_InitSystems(std::move(ctxProcess));
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
            inst._ctxProcess->ptrProcessor->IUpdate(globalAccessor);

            while (timeSystem._ShouldFixedUpdate())
            {
                inst._ctxProcess->ptrProcessor->IFixedUpdate(globalAccessor);
                #warning "TODO: Physics logic goes here"
            }

            render::DrawHandle drawHandle {*inst._ctxProcess->ptrRenderSys};
            inst._ctxProcess->ptrProcessor->IDraw(drawHandle);
            inst._ctxProcess->ptrRenderSys->IDraw();
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
