#pragma once

#include "engine/core/i_processor.hpp"
#include "engine/system/time_system.hpp"
#include "engine/system/audio_system.hpp"
#include "engine/util/window_context.hpp"

#include <vendor/zutil/zutil.hpp>

namespace dull::core
{

    // ---
    // Main application
    // ---
    struct App final : public zutil::Logger
    {
    private:
        bool _isRunning = false;

        static void _InitSystems(IProcessor* processorPtr) noexcept;
        static void _ShutdownSystems() noexcept;

    public:
        system::TimeSystem  timeSystem;
        system::AudioSystem audioSystem;

        App();
        ~App();

        App(App&&)                 = delete;
        App(const App&)            = delete;
        App& operator=(App&&)      = delete;
        App& operator=(const App&) = delete;

        [[nodiscard]] static App& GetInstance() noexcept;
        [[nodiscard]] static bool IsRunning() noexcept;

        static void Init(const util::WindowContext& windowContext, IProcessor* processorPtr = nullptr) noexcept;
        static void Run() noexcept;
        static void Quit() noexcept;
    };

} // namespace dull::core

#define DULL_APP_INST \
    ::dull::core::App::GetInstance()
