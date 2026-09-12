#pragma once

#include "engine/config.hpp"
#include "engine/core/window.hpp"
#include "engine/core/audio_system.hpp"
#include "engine/core/time_system.hpp"
#include "engine/render/renderer.hpp"

#include <zen/log.hpp>

#include <memory>

// Forward Declaration
namespace dull::core { struct IProcessor; }

namespace dull::util {

    struct WindowContext final {
        std::string title {config::GetConfigString()};
        core::Window::Dimension dimension {600, 800};
        bool isVsync {false};
        bool isResizeable {false};
    };

    struct ProcessContext final {
        core::IProcessor*    ptrProcessor {nullptr};
        render::IRenderer* ptrRenderSys {nullptr};
    };

    struct GlobalAccessor final {
        core::Window&      refWindow;
        core::TimeSystem&  refTime;
        core::AudioSystem& refAudio;
    };

} // namespace dull::util

namespace dull::core {

    struct Engine final {
    private:
        static const zen::log_tag _LOG;
        bool _isRunning {false};
        bool _isInitialized {false};

        std::unique_ptr<util::WindowContext> _ctxWindow;
        std::unique_ptr<util::ProcessContext> _ctxProcess;

        Engine() = default;
        ~Engine();

        static void _InitWindow(const util::WindowContext&& ctxWindow) noexcept;
        static void _InitSystems(const util::ProcessContext&& ctxProcess) noexcept;
        static void _ShutdownSystems() noexcept;

    public:
        TimeSystem  timeSys;
        AudioSystem audioSys;
        Window      window;

        Engine(Engine&&)                 = delete;
        Engine(const Engine&)            = delete;
        Engine& operator=(Engine&&)      = delete;
        Engine& operator=(const Engine&) = delete;

        [[nodiscard]] static Engine& GetInstance() noexcept;
        [[nodiscard]] static bool IsRunning() noexcept { return GetInstance()._isRunning; }
        [[nodiscard]] static bool IsInitialized() noexcept { return GetInstance()._isInitialized; }

        static void Init(const util::WindowContext&& ctxWindow) noexcept;
        static void Run(util::ProcessContext ctxProcess) noexcept;
        static void Quit() noexcept;
    };

} // namespace dull::core

#define DULL_INST \
    ::dull::core::Engine::GetInstance()
