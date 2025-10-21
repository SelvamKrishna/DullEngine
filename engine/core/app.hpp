#pragma once

#include "engine/util/vec2.hpp"

#include <string>

namespace dull::core {

struct AppConfig final {
  std::string title;
  util::Vec2i window_size {1280, 720};
  int target_fps {0}; // 0 disables frame limiting
  bool is_vsync {true};
  bool is_resizeable {true};
};

class App final {
private:
  static inline App* s_instance = nullptr;
  bool _is_running {false};

public:
  App() = delete;
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  explicit App(const AppConfig& config);
  ~App() noexcept;

  [[nodiscard]] App& instance() noexcept { return *s_instance; }

  void run();
};

} // namespace dull::core