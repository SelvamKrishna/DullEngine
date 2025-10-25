#include "engine/core/app.hpp"
#include "engine/config.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>

#include <format>
#include <string>
#include <cassert>

namespace dull::core {

static inline App* s_instance {nullptr};

App::App(const misc::AppConfig& config) {
  assert(s_instance == nullptr);

#ifdef NDEBUG
  const std::string& TITLE = config.title;
#else
  const std::string TITLE = std::format(
    "Dull Engine v{} - {}", config::getVerString(), config.title
  );
#endif

  int flags {
    (config.is_vsync ? FLAG_VSYNC_HINT : 0) |
    (config.is_resizeable ? FLAG_WINDOW_RESIZABLE : 0)
  };

  SetConfigFlags(flags);
  InitWindow(config.window_size.x, config.window_size.y, TITLE.c_str());
  SetExitKey(KEY_NULL);
  SetTargetFPS(config.target_fps);

  _is_running = true;
  s_instance = this;
}

App::~App() noexcept { if (_is_running) CloseWindow(); }

[[nodiscard]] App& App::instance() noexcept { return *s_instance; }

void App::run() {
  while (!WindowShouldClose()) [[likely]] {
    /// TODO: Should be replaced with RenderSystem
    ClearBackground(BLACK);
    BeginDrawing();
    DrawFPS(10, 10);
    EndDrawing();
  }
}

} // namespace dull::core
