#pragma once

#include "engine/config.hpp"
#include "engine/core/processor.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"

#include <zen/log.hpp>

#include <utility>

namespace dull::util {

    struct WindowContext final {
        std::string         title        {config::GetConfigString()};
        std::pair<int, int> dimension    {640, 640};
        bool                isVsync      {false};
        bool                isResizeable {false};
    };

    struct ProcessContext final {
        core::IProcessor* processorPtr {nullptr};
    };

    struct GlobalAccessor final {
        system::TimeSystem&  timeRef;
        system::AudioSystem& audioRef;
    };

} // namespace dull::util

namespace dull::core {

    struct Engine final {
    private:
        bool _isRunning {false};

        zen::log_tag _logTag {
            "[DULL]",
            zen::ansi_color::BG_BLACK,
            const_cast<zen::log_tag*>(&config::DULL_TAG)
        };

        static void _InitSystems(const util::ProcessContext& processContext) noexcept;
        static void _ShutdownSystems() noexcept;

    public:
        system::TimeSystem timeSystem;
        system::AudioSystem audioSystem;

        explicit Engine();
        ~Engine();

        Engine(Engine&&)                 = delete;
        Engine(const Engine&)            = delete;
        Engine& operator=(Engine&&)      = delete;
        Engine& operator=(const Engine&) = delete;

        [[nodiscard]] static Engine& GetInstance() noexcept;
        [[nodiscard]] static bool IsRunning() noexcept;

        static void Init(const util::WindowContext& windowContext) noexcept;
        static void Run(const util::ProcessContext& processContext) noexcept;
        static void Quit() noexcept;
    };

} // namespace dull::core

#define DULL_APP_INST \
    ::dull::core::Engine::GetInstance()
