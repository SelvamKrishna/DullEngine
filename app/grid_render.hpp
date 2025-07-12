#pragma once

#include "../source/plugins/render_system.hpp"

class GridRenderSystem : public RenderSystem {
private:
  virtual void _update() final {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    for (int x = 0; x < GetScreenWidth(); x += 20) {
      DrawLine(x, 0, x, GetScreenHeight(), LIGHTGRAY);
    }
    for (int y = 0; y < GetScreenHeight(); y += 20) {
      DrawLine(0, y, GetScreenWidth(), y, LIGHTGRAY);
    }

    EndDrawing();
  }
};
