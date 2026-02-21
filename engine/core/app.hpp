#pragma once

#include "engine/process/i_processor.hpp"
#include "engine/system/time_system.hpp"
#include "engine/util/window_context.hpp"

#include <vendor/zutil/zutil.hpp>

namespace dull::core {

// ---
// Main application
// ---
struct App final : public zutil::Logger {
private:
    bool _isRunning = false;

    static void _InitSystems(process::IProcessor* processorPtr) noexcept;

public:
    system::TimeSystem timeSystem;

    App(App&&)                 = delete;
    App(const App&)            = delete;
    App& operator=(App&&)      = delete;
    App& operator=(const App&) = delete;

    App();
    ~App();

    [[nodiscard]] static App& GetInstance() noexcept;
    [[nodiscard]] static bool IsRunning() noexcept;

    static void Init(const util::WindowContext& windowContext) noexcept;
    static void Run(process::IProcessor* processorPtr) noexcept;
    static void Quit() noexcept;
};

} // namespace dull::core
