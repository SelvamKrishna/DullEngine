#pragma once

#include "../source/plugins/render_system.hpp"
#include "../source/utils/vec2.hpp"
#include "grid.hpp"

class GridRenderSystem : public RenderSystem {
private:
  Grid* _grid;

protected:
  virtual void _update() final {
    static Vec2 cell_size;
    cell_size.x = (float)GetScreenWidth() / _grid->getWidth();
    cell_size.y = (float)GetScreenHeight() / _grid->getHeight();
    BeginDrawing();
    ClearBackground(WHITE);

    for (size_t row = 0; row < _grid->getHeight(); ++row) {
      for (size_t col = 0; col < _grid->getWidth(); ++col) {
        if (_grid->getCell(row, col) == 1) {
          DrawRectangle(col * cell_size.x, row * cell_size.y, cell_size.x, cell_size.y, BLACK);
        } else {
          DrawRectangleLines(col * cell_size.x, row * cell_size.y, cell_size.x, cell_size.y, GRAY);
        }
      }
    }

    DrawFPS(10, 10);
    EndDrawing();
  }

public:
  static GridRenderSystem& instance() {
    static GridRenderSystem instance;
    return instance;
  }

  void setGrid(Grid* grid) { _grid = grid; }
};
