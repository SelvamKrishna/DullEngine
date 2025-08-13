#include "gol_grid.hpp"

#include <cstddef>

uint8_t CellGrid::_countNeighbours(size_t x, size_t y) const noexcept {
    uint8_t neighbour_count = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            if (dx == 0 && dy == 0) [[unlikely]] continue;

            size_t nx = (x + dx + COL_COUNT) % COL_COUNT;
            size_t ny = (y + dy + ROW_COUNT) % ROW_COUNT;

            CellState cell_state = _grid[nx][ny];
            if (cell_state == CellState::Alive || cell_state == CellState::Dying) neighbour_count++;
        }
    }

    return neighbour_count;
}

inline void CellGrid::_fillRandom() noexcept {
    for (size_t x = 0; x < COL_COUNT; ++x) {
        for (size_t y = 0; y < ROW_COUNT; ++y) {
            _grid.at(x).at(y) = GetRandomValue(0, 1) == 1
                ? CellState::Alive 
                : CellState::Dead;
        }
    }
}

inline void CellGrid::_fillEmpty() noexcept {
    for (size_t x = 0; x < COL_COUNT; ++x) {
        for (size_t y = 0; y < ROW_COUNT; ++y) {
            _grid.at(x).at(y) = CellState::Dead;
        }
    }
}

void CellGrid::_init() { _fillRandom(); }

void CellGrid::_update() {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) [[unlikely]] {
        const size_t X_CELL_POS = GetMouseX() / GameInfo::Custom::PIXEL_SIZE;
        const size_t Y_CELL_POS = GetMouseY() / GameInfo::Custom::PIXEL_SIZE;

        if (X_CELL_POS < COL_COUNT && Y_CELL_POS < ROW_COUNT)
            _grid.at(X_CELL_POS).at(Y_CELL_POS) = CellState::Birth;
    }

    if (IsKeyPressed(KEY_SPACE)) [[unlikely]] _simulate = !_simulate;
    if (IsKeyPressed(KEY_C))     [[unlikely]] _fillEmpty();
    if (IsKeyPressed(KEY_R))     [[unlikely]] _fillRandom(); 
}

void CellGrid::_fixedUpdate() {
    if (!_simulate) return;

    for (size_t x = 0; x < COL_COUNT; ++x) {
        for (size_t y = 0; y < ROW_COUNT; ++y) {
            auto& cell = _grid.at(x).at(y);
            uint8_t neighbour_count = _countNeighbours(x, y);

            if (cell == CellState::Alive && (neighbour_count < 2 || neighbour_count > 3)) 
                cell = CellState::Dying;
            else if (cell == CellState::Dead && neighbour_count == 3)
                cell = CellState::Birth;
        }
    }
}