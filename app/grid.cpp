#include "grid.hpp"

#include <algorithm>
#include <cstdint>
#include <vector>

#include "../vendor/raylib.h"

Grid::Grid(uint8_t rows, uint8_t cols) : Node("Grid") {
    _grid.resize(cols, std::pmr::vector<uint8_t>(rows, 0));
}

Grid::~Grid() = default;

void Grid::_init() {
    for (auto &row : _grid) {
        std::ranges::fill(row, 0);
    }
}

void Grid::_update() {
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) [[unlikely]] {
        auto row = static_cast<size_t>((float)GetMouseY() / ((float)GetScreenHeight() / (float)_grid.size()));
        auto col =
            static_cast<size_t>((float)GetMouseX() / ((float)GetScreenWidth() / (float)_grid[0].size()));
        if (row < _grid.size() && col < _grid[0].size()) {
            _grid[row][col] = 1;
        }
    }

    if (IsKeyPressed(KEY_C)) [[unlikely]] {
        for (auto &row : _grid) {
            std::ranges::fill(row, 0);
        }
    }
}
