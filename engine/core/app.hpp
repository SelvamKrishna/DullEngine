#pragma once

#include "engine/misc/app_config.hpp"

namespace dull::core {

class App final {
private:
  bool _is_running {false};

public:
  App() = delete;
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  explicit App(const misc::AppConfig& config);
  ~App() noexcept;

  [[nodiscard]] static App& instance() noexcept;

  void run();
};

} // namespace dull::core
