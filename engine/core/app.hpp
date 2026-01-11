#pragma once

#include "engine/core/handle.hpp"
#include "engine/system/audio_system.hpp"
#include "engine/system/event_system.hpp"
#include "engine/system/time_system.hpp"
#include "engine/util/vec2.hpp"

// Forward Include
#include "engine/process/world.hpp" // IWYU pragma: keep
#include "engine/process/scene.hpp" // IWYU pragma: keep
#include "engine/process/layer.hpp" // IWYU pragma: keep
#include "engine/process/node.hpp"  // IWYU pragma: keep

#include <vendor/zlog_v2.hpp>

namespace dull::core {

// =======================
// Window Configuration
// =======================
struct AppContext final {
    std::string title         = config::TITLE;
    util::Vec2i window_size   = config::WINDOW_SIZE;
    bool        is_vsync      = config::IS_VSYNC;
    bool        is_resizeable = config::IS_RESIZEABLE;

    void logStats() const noexcept;
};

// =======================
// Main application
// =======================
class App final {
    friend Handle;

private:
    system::AudioSystem _audio_sys;
    system::EventSystem _event_sys;
    system::TimeSystem  _time_sys;

    config::Processor   _processor; //< change in dull::config

    Handle _handle { { _audio_sys, _event_sys, _time_sys, _processor } };

public:
    App(App&&)                 = delete;
    App(const App&)            = delete;
    App& operator=(App&&)      = delete;
    App& operator=(const App&) = delete;

    App(const AppContext& context = {});
    ~App() noexcept;

    [[nodiscard]]
    static App& instance() noexcept;

    [[nodiscard]]
    const Handle& getHandle() noexcept { return _handle; }

    void run() noexcept;
    void quit() noexcept;
};

} // namespace dull::core

/// MACROS:

#define DULL_HANDLE ::dull::core::App::instance().getHandle()
#define DULL_CTX    ::dull::core::App::instance().getHandle().ctx
