#pragma once

#include "engine/core/processor.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zenutil/zen_prelude.hpp>

namespace dull::util {

    struct WindowContext final {
        std::string title        = config::GetConfigString();
        util::Vec2i dimension    = {640, 640};
        bool        isVsync      = false;
        bool        isResizeable = false;
    };

    struct ProcessContext final {
        core::IProcessor* processorPtr = nullptr;
    };

} // namespace dull::util

namespace dull::core {

    struct Engine final : public zen::core::Logger {
    private:
        bool _isRunning = false;

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
