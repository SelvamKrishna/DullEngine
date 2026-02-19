#pragma once

#include "engine/process/i_processor.hpp"
#include "engine/system/system_handle.hpp"
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
    bool _isRunning = false;

public:
    system::SystemHandle systems;

    App(App&&)                 = delete;
    App(const App&)            = delete;
    App& operator=(App&&)      = delete;
    App& operator=(const App&) = delete;

    explicit App(const system::SystemContext& systemContext = {}, const WindowContext& windowContext = {});

    ~App() noexcept;

    [[nodiscard]] static App& GetInstance() noexcept;
    [[nodiscard]] bool IsRunning() const noexcept { return this->_isRunning; }

    void Run() noexcept;
    void Quit() noexcept;
};

} // namespace dull::core
