#include "engine/core/app.hpp"

#include "engine/config.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/raylib.h>

#include <format>
#include <string>
#include <cassert>

namespace dull::core {

App::App(const AppConfig& ctx) {
  assert(s_instance == nullptr);

  const std::string TITLE {
    #ifdef DULL_MODE_DEBUG
    std::format("Dull Engine v{} - {}", config::getVerString(), ctx.title)
    #else
    ctx.title
    #endif
  };

  int flags {
    (ctx.is_vsync ? FLAG_VSYNC_HINT : 0) |
    (ctx.is_resizeable ? FLAG_WINDOW_RESIZABLE : 0)
  };

  SetConfigFlags(flags);
  InitWindow(ctx.window_size.x, ctx.window_size.y, TITLE.c_str());
  SetTargetFPS(ctx.target_fps);
  SetExitKey(KEY_NULL);

  _is_running = true;
  s_instance = this;
}

App::~App() noexcept { if (_is_running) CloseWindow(); }

void App::run() {
  while (!WindowShouldClose()) [[likely]] {
    /// TODO: Should be replaced with RenderSystem
    ClearBackground(BLACK);
    BeginDrawing();
    EndDrawing();
  }
}

} // namespace dull::core