#pragma once

#include "engine/process/i_processor.hpp"
#include "engine/system/time_system.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zutil/zutil.hpp>

#include <string>

namespace dull::core {

// ---
// Window configuration
// ---
struct WindowContext final {
    std::string title          = "Application";
    util::Vec2i dimension      = {800, 600};
    bool        isVsyncEnabled = false;
    bool        isResizeable   = false;
};

// ---
// Main application
// ---
struct App final : public zutil::Logger {
private:
    system::TimeSystem _timeSystem;
    process::IProcessor& _processor;
    bool _isRunning = false;

public:
    App(App&&)                 = delete;
    App(const App&)            = delete;
    App& operator=(App&&)      = delete;
    App& operator=(const App&) = delete;

    explicit App(const WindowContext& windowContext = {}, process::IProcessor* processorPtr = nullptr);
    ~App() noexcept;

    [[nodiscard]] static App& GetInstance() noexcept;
    [[nodiscard]] bool IsRunning() const noexcept { return this->_isRunning; }
    [[nodiscard]] system::TimeSystem& GetTimeSystem() noexcept { return this->_timeSystem; }
    [[nodiscard]] process::IProcessor& GetProcessor() noexcept { return this->_processor;  }

    void Run() noexcept;
    void Quit() noexcept;
};

} // namespace dull::core

/// MACROS:

#define DULL_HANDLE ::dull::core::App::GetInstance().GetHandle()
#define DULL_CTX    ::dull::core::App::GetInstance().GetHandle().context
