#include "grid_render.hpp"

#include "../vendor/raylib.h"

void GridRenderSystem::_update() {
    int cell_size_x = GetScreenWidth() / _grid->getWidth();
    int cell_size_y = GetScreenHeight() / _grid->getHeight();

    BeginDrawing();
    ClearBackground(WHITE);

    for (int row = 0; row < _grid->getHeight(); ++row) {
        for (int col = 0; col < _grid->getWidth(); ++col) {
            int posX = col * cell_size_x;
            int posY = row * cell_size_y;

            if (_grid->getCell(row, col) == 1) {
                DrawRectangle(posX, posY, cell_size_x, cell_size_y, BLACK);
            }

            DrawRectangleLines(posX, posY, cell_size_x, cell_size_y, GRAY);
        }
    }

    DrawFPS(10, 10);
    EndDrawing();
}
