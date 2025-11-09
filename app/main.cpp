#include "engine/core/app.hpp"

int main(void) {
  dull::core::App app {
    dull::misc::AppContext {
      .title = "My Dull Application",
      .window_size = dull::util::Vec2i {800, 600},
      .target_fps = 60,
      .is_vsync = true,
      .is_resizeable = true,
    }
  };

  return app.run();
}
