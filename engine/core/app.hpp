#pragma once

#include "engine/core/event_sys.hpp"
#include "engine/misc/app_context.hpp"

namespace dull::core {

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

    explicit App(const misc::AppContext& context);
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
