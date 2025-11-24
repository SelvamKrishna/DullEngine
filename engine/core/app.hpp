#pragma once

#include "engine/core/event_sys.hpp"
#include "engine/misc/app_context.hpp"

namespace dull::core {

class App final {
private:
  bool _is_running = false;

  EventBus _event_bus;

public:
  App() = delete;

  App(App&&)                 = delete;
  App(const App&)            = delete;
  App& operator=(App&&)      = delete;
  App& operator=(const App&) = delete;

  explicit App(const misc::AppContext& context);
  ~App() noexcept;

  [[nodiscard]] static App& instance() noexcept;
  [[nodiscard]] EventBus&   getEventBus() noexcept { return _event_bus; }

  int run() noexcept;

};

} // namespace dull::core
