#pragma once

#include "engine/core/event_bus.hpp"
#include "engine/core/scene.hpp"
#include "engine/core/handle.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zutils/tools.hpp>

namespace dull::core {

// =======================
// Window Configuration
// =======================
struct AppContext final {
    std::string title         = "Application";
    util::Vec2i window_size   = {800, 800};
    int         target_fps    = 0;     // if 0 no max capping of fps
    bool        is_vsync      = false; // caps fps to monitor refresh rate
    bool        is_resizeable = false;

    [[nodiscard]]
    static AppContext load() noexcept;
};

// =======================
// Main application
// =======================
class App final {
    friend class Handle;

private:
    EventBus    _event_bus;
    SceneSystem _scene_sys;
    Handle      _handle;
    bool   _is_running = false;

public:
    App() = delete;

    App(App&&)                 = delete;
    App(const App&)            = delete;
    App& operator=(App&&)      = delete;
    App& operator=(const App&) = delete;

    App(const AppContext& context);
    ~App() noexcept;

    [[nodiscard]]
    static App& instance() noexcept;

    [[nodiscard]]
    Handle& handle() noexcept { return _handle; }

    [[nodiscard]]
    constexpr bool isRunning() const noexcept { return _is_running; }

    void run()  noexcept;
    void quit() noexcept { _is_running = false; }

    void logStats() const noexcept;
};

} // namespace dull::core

#define HANDLE  ::dull::core::App::instance().handle()
