#pragma once

#include "../source/plugins/render_system.hpp"

class GridRenderSystem : public RenderSystem {
protected:
  virtual void _update() final {
    BeginDrawing();
    ClearBackground(WHITE);

    for (int x = 0; x < GetScreenWidth(); x += 20) DrawLine(x, 0, x, GetScreenHeight(), BLACK);
    for (int y = 0; y < GetScreenHeight(); y += 20) DrawLine(0, y, GetScreenWidth(), y, BLACK);

    DrawFPS(10, 10);
    EndDrawing();
  }

public:
  static GridRenderSystem& instance() {
    static GridRenderSystem instance;
    return instance;
  }
};
