#include "gol_render.hpp"
#include "gol_grid.hpp"
#include "../source/core/app.hpp"
#include "../vendor/raylib.h"

#include <cstddef>
#include <memory>

void CellRenderSystem::_init() { 
    _cell_grid_ref = CURRENT_SCENE.getNode<CellGrid>(); 

    _observer = std::make_shared<Observer>([this]() {
        if (_show_help_ui) DULL_LOG("Menu: ON");
        else DULL_LOG("Menu: OFF");
    });

    _observer->attachSignal("menu_toggle");
}

void CellRenderSystem::_update() {
    if (IsKeyPressed(KEY_ESCAPE)) [[unlikely]] {
        _show_help_ui = !_show_help_ui;
        SIGNAL_SYS.emitSignal("menu_toggle");
    }

    BeginDrawing();
    ClearBackground(GameInfo::Custom::DEAD_COLOR);

    if (_show_help_ui) {
        static constexpr int TEXT_X_POS = 25;
        static constexpr int FONT_SIZE = 20;
        static constexpr int TEXT_Y_OFFSET = 40;
        static constexpr int TEXT_Y_PADDING = 20;

        for (size_t i = 0; i < HELP_UI_TEXT_LIST.size(); i++) {
            DrawText(
                HELP_UI_TEXT_LIST[i].data(), 
                TEXT_X_POS,
                TEXT_Y_OFFSET + (i * TEXT_Y_PADDING),
                FONT_SIZE, 
                ColorRGBA::red()
            );
        }
    }

    if (auto cell_grid = _cell_grid_ref.lock()) {
        auto& grid = cell_grid->grid();

        for (size_t x = 0; x < CellGrid::COL_COUNT; ++x) {
            for (size_t y = 0; y < CellGrid::ROW_COUNT; ++y) {
                auto& cell = grid.at(x).at(y);

                if (cell == CellState::Birth) cell = CellState::Alive;
                else if (cell == CellState::Dying) cell = CellState::Dead;

                if (cell == CellState::Alive) [[unlikely]] {
                    DrawRectangle(
                        static_cast<int>(x * GameInfo::Custom::PIXEL_SIZE),
                        static_cast<int>(y * GameInfo::Custom::PIXEL_SIZE),
                        GameInfo::Custom::PIXEL_SIZE,
                        GameInfo::Custom::PIXEL_SIZE,
                        GameInfo::Custom::ALIVE_COLOR
                    );
                }
            }
        }
    }

    DrawFPS(10, 10);
    EndDrawing();
}