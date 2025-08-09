#include "gol_grid.hpp"

uint8_t CellGrid::_countNeighbours(size_t x, size_t y) const noexcept {
    uint8_t neighbour_count = 0;

    for (int dx = -1; dx < 2; ++dx) {
        for (int dy = -1; dy < 2; ++dy) {
            if (dx == 0 && dy == 0) [[unlikely]] {
                continue;
            }

            size_t nx = (x + dx + COL_COUNT) % COL_COUNT;
            size_t ny = (y + dy + ROW_COUNT) % ROW_COUNT;

            auto cell_state = _grid[nx][ny];
            if (cell_state == CellState::Alive || cell_state == CellState::Dying) {
                ++neighbour_count;
            }
        }
    }

    return neighbour_count;
}

void CellGrid::_init() {
    setUpdate(false);
    setFixedUpdate(true);

    for (size_t x = 0; x < COL_COUNT; ++x) {
        for (size_t y = 0; y < ROW_COUNT; ++y) {
            _grid.at(x).at(y) = GetRandomValue(0, 1) == 1 ? CellState::Alive : CellState::Dead;
        }
    }
}

void CellGrid::_fixedUpdate() {
    for (size_t x = 0; x < COL_COUNT; ++x) {
        for (size_t y = 0; y < ROW_COUNT; ++y) {
            auto &cell = _grid.at(x).at(y);
            uint8_t neighbour_count = _countNeighbours(x, y);

            if (cell == CellState::Alive && (neighbour_count < 2 || neighbour_count > 3)) {
                cell = CellState::Dying;
            } else if (cell == CellState::Dead && neighbour_count == 3) {
                cell = CellState::Birth;
            }
        }
    }
}