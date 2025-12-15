#pragma once

#include "engine/core/event_bus.hpp"
#include "engine/core/handle.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

// =======================
// Window Configuration
// =======================
struct AppContext final {
    std::string title         = "Application";
    util::Vec2i window_size   = {800, 800};
    bool        is_vsync      = false;
    bool        is_resizeable = false;

    [[nodiscard]]
    static AppContext load() noexcept;

    void logStats() const noexcept;
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
    Handle& getHandle() noexcept { return _handle; }

    [[nodiscard]]
    constexpr bool isRunning() const noexcept { return _is_running; }

    void  run() noexcept;
    void quit() noexcept { _is_running = false; }
};

} // namespace dull::core

#define DULL_HANDLE \
    ::dull::core::App::instance().getHandle()
