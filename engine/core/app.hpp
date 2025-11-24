#pragma once

#include "engine/core/event_sys.hpp"
#include "engine/misc/app_context.hpp"

namespace dull::core {

class App final {
private:
  bool _is_running {false};

  EventBus _event_bus;

public:
  App() = delete;
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  explicit App(const misc::AppContext& context);
  ~App() noexcept;

  [[nodiscard]] static App& instance() noexcept;

  int run() noexcept;

  [[nodiscard]] EventBus& getEventBus() noexcept;
};

} // namespace dull::core
