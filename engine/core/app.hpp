#pragma once

#include "engine/core/event_sys.hpp"
#include "engine/misc/app_context.hpp"

namespace dull::core {

class App final {
private:
  bool _is_running {false};

  EventSystem _event_sys;

public:
  App() = delete;
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  explicit App(const misc::AppContext& context);
  ~App() noexcept;

  [[nodiscard]] static App& instance() noexcept;

  int run();

  [[nodiscard]] EventSystem& getEventSystem() noexcept;
};

} // namespace dull::core
