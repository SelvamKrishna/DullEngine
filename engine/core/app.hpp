#pragma once

#include "engine/core/handle.hpp"
#include "engine/system/time_sys.hpp"
#include "engine/system/event_sys.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

// =======================
// Window Configuration
// =======================
struct AppContext final {
    std::string title         = config::TITLE;
    util::Vec2i window_size   = config::WINDOW_SIZE;
    bool        is_vsync      = config::IS_VSYNC ;
    bool        is_resizeable = config::IS_RESIZEABLE;

    void logStats() const noexcept;
};

// =======================
// Main application
// =======================
class App final {
    friend Handle;

private:
    sys::TimeSystem _time_sys;
    sys::EventSystem _event_sys;
    config::Processor _processor;

    Handle _handle { {
        _time_sys,
        _event_sys,
        _processor,
    } };

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
    const Handle& getHandle() noexcept { return _handle; }

    void run() noexcept;
    void quit() noexcept;
};

} // namespace dull::core

#define DULL_HANDLE ::dull::core::App::instance().getHandle()
#define DULL_CTX    DULL_HANDLE.ctx
