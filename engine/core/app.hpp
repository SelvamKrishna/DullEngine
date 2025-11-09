#pragma once

#include "engine/core/event.hpp"
#include "engine/misc/app_config.hpp"

namespace dull::core {

class App final {
private:
  bool _is_running {false};

  EventBus _event_bus {};

public:
  App() = delete;
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  explicit App(const misc::AppConfig& config);
  ~App() noexcept;

  [[nodiscard]] static App& instance() noexcept;

  void run();

  [[nodiscard]] EventBus& getEventBus() noexcept { return _event_bus; }
};

} // namespace dull::core
