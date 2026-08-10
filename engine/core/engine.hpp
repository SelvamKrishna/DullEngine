#pragma once

#include "engine/config.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"

#include <zen/log.hpp>

#include <memory>
#include <utility>

// Forward Declaration
namespace dull::core { class IProcessor; }

namespace dull::util {

    struct WindowContext final {
        std::string         title        {config::GetConfigString()};
        std::pair<int, int> dimension    {640, 640};
        bool                isVsync      {false};
        bool                isResizeable {false};
    };

    struct ProcessContext final {
        core::IProcessor* processorPtr;
    };

    struct GlobalAccessor final {
        const std::pair<int, int> WINDOW_SIZE;
        system::TimeSystem&  timeRef;
        system::AudioSystem& audioRef;
    };

} // namespace dull::util

namespace dull::core {

    struct Engine final {
    private:
        static const zen::log_tag _LOG;
        bool _isRunning {false};
        bool _isInitialized {false};

        std::unique_ptr<util::WindowContext> _windowContext;
        std::unique_ptr<util::ProcessContext> _processContext;

        Engine() = default;
        ~Engine();

        static void _InitWindow(const util::WindowContext&& windowContext) noexcept;
        static void _InitSystems(const util::ProcessContext&& processContext) noexcept;
        static void _ShutdownSystems() noexcept;

    public:
        system::TimeSystem  timeSys;
        system::AudioSystem audioSys;

        Engine(Engine&&)                 = delete;
        Engine(const Engine&)            = delete;
        Engine& operator=(Engine&&)      = delete;
        Engine& operator=(const Engine&) = delete;

        [[nodiscard]] static Engine& GetInstance() noexcept;
        [[nodiscard]] static bool IsRunning() noexcept { return GetInstance()._isRunning; }
        [[nodiscard]] static bool IsInitialized() noexcept { return GetInstance()._isInitialized; }

        static void Init(const util::WindowContext&& windowContext) noexcept;
        static void Run(util::ProcessContext processContext) noexcept;
        static void Quit() noexcept;
    };

} // namespace dull::core

#define DULL_INST \
    ::dull::core::Engine::GetInstance()
