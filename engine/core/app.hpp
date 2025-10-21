#pragma once

#include "engine/util/vec2.hpp"

#include <string>

namespace dull::core {

struct AppContext final {
  std::string title;
  util::Vec2i window_size {1280, 720};
  int target_fps {0}; // 0 disables frame_limiting
  bool is_vsync {true};
  bool is_resizeable {true};
};

class App final {
private:
  bool _is_running {false};

public:
  App() = delete;
  App(const App&) = delete;
  App& operator=(const App&) = delete;

  explicit App(const AppContext& ctx);
  ~App() noexcept;

  void run();
};

} // namespace dull::core