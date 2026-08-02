#pragma once

#include "engine/config.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"

#include <zen/log.hpp>

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
        core::IProcessor* processorPtr {nullptr};
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
        static inline const zen::log_tag _LOG {"APP", zen::ansi_color::BLUE, &config::DULL_TAG};
        bool _isRunning {false};

        static void _InitSystems(const util::ProcessContext& processContext) noexcept;
        static void _ShutdownSystems() noexcept;

        explicit Engine();

    public:
        system::TimeSystem timeSystem;
        system::AudioSystem audioSystem;

        Engine(Engine&&)                 = delete;
        Engine(const Engine&)            = delete;
        Engine& operator=(Engine&&)      = delete;
        Engine& operator=(const Engine&) = delete;

        [[nodiscard]] static Engine& GetInstance() noexcept;
        [[nodiscard]] static bool IsRunning() noexcept;

        static void Init(const util::WindowContext& windowContext) noexcept;
        static void Run(util::ProcessContext processContext) noexcept;
        static void Quit() noexcept;
    };

} // namespace dull::core

#define DULL_INST \
    ::dull::core::Engine::GetInstance()

