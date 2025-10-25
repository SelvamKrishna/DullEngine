#pragma once

#include "engine/util/vec2.hpp"

#include <string>

namespace dull::misc {

struct AppConfig final {
  std::string title;
  util::Vec2i window_size {1280, 720};
  int target_fps {0}; // 0 disables frame limiting
  bool is_vsync {false}; // limits frame to monitor cap
  bool is_resizeable {false};
};

} // namespace dull::misc
