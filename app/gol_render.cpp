#include "gol_render.hpp"

#include "../source/core/app.hpp"
#include "gol_grid.hpp"
#include <memory>

void CellRenderSystem::_init() { _cell_grid_ref = CURRENT_SCENE.getNode<CellGrid>(); }

void CellRenderSystem::_update() {
    BeginDrawing();
    ClearBackground(GameInfo::Custom::DEAD_COLOR);

    if (auto cell_grid = _cell_grid_ref.lock()) {
        auto &grid = cell_grid->grid();

        for (size_t x = 0; x < CellGrid::COL_COUNT; ++x) {
            for (size_t y = 0; y < CellGrid::ROW_COUNT; ++y) {
                auto &cell = grid.at(x).at(y);

                if (cell == CellState::Birth) {
                    cell = CellState::Alive;
                } else if (cell == CellState::Dying) {
                    cell = CellState::Dead;
                }

                if (cell == CellState::Alive) {
                    DrawRectangle(static_cast<int>(x * GameInfo::Custom::PIXEL_SIZE),
                                  static_cast<int>(y * GameInfo::Custom::PIXEL_SIZE),
                                  GameInfo::Custom::PIXEL_SIZE,
                                  GameInfo::Custom::PIXEL_SIZE,
                                  GameInfo::Custom::ALIVE_COLOR);
                }
            }
        }
    }

    DrawFPS(10, 10);
    EndDrawing();
}