#include "grid_render.hpp"
#include "../source/utils/vec2.hpp"

void GridRenderSystem::_update() {
    static Vec2 cell_size;
    cell_size.x = (float)GetScreenWidth() / (float)_grid->getWidth();
    cell_size.y = (float)GetScreenHeight() / (float)_grid->getHeight();
    Color cell_color;

    BeginDrawing();
    ClearBackground(WHITE);

    for (int row = 0; row < _grid->getHeight(); ++row) {
        for (int col = 0; col < _grid->getWidth(); ++col) {
            cell_color = _grid->getCell(row, col) == 1 ? BLACK : GRAY;

            DrawRectangleLines(col * (int)cell_size.x,
                               row * (int)cell_size.y,
                               (int)cell_size.x,
                               (int)cell_size.y,
                               cell_color);
        }
    }

    DrawFPS(10, 10);
    EndDrawing();
}