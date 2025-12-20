#pragma once

#include "engine/core/event_system.hpp"
#include "engine/core/scene_system.hpp"
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
    friend Handle;

private:
    EventSystem _event_sys;
    SceneSystem _scene_sys;

    Handle _handle {
        _event_sys,
        _scene_sys,
        _scene_sys.getLayerBuffer(),
        _scene_sys.getSceneBuffer(),
    };

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

    void  run() noexcept;
    void quit() noexcept;
};

} // namespace dull::core

#define DULL_HANDLE \
    ::dull::core::App::instance().getHandle()
