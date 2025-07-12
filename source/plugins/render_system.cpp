#include "render_system.hpp"

void RenderSystem::_update() {
  BeginDrawing();
  ClearBackground(BLACK);
  DrawFPS(10, 10);
  EndDrawing();
}