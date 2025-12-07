#pragma once

#include "engine/core/event_bus.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zutils/tools.hpp>

namespace dull::core {

struct AppContext final {
    std::string title         = "Application";
    util::Vec2i window_size   = {800, 800};
    int         target_fps    = 0;
    bool        is_vsync      = false;
    bool        is_resizeable = false;

    [[nodiscard]]
    static AppContext load()
    {
        ZTODO("Load AppContext from config file");
        return {/*TODO*/};
    }
};

class App final {
private:
    EventBus _event_bus;
    bool     _is_running = false;

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
    constexpr bool isRunning() const noexcept { return _is_running; }

    [[nodiscard]]
    EventBus& getEventBus() noexcept { return _event_bus; }

    void run()  noexcept;
    void quit() noexcept { _is_running = false; }

    void logStats() const noexcept;
};

} // namespace dull::core
