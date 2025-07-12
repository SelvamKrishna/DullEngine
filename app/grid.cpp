#include "grid.hpp"

#include <cstdint>
#include <vector>

#include "../vendor/raylib.h"

Grid::Grid(uint8_t width, uint8_t height) : Node("Grid") {
  _grid.resize(height, std::pmr::vector<uint8_t>(width, 0));
}

Grid::~Grid() {}

void Grid::_init() {
  for (auto &row : _grid) std::fill(row.begin(), row.end(), 0);
}

void Grid::_update() {
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) [[unlikely]] {
    size_t row = static_cast<size_t>(GetMouseY() / ((float)GetScreenHeight() / _grid.size()));
    size_t col = static_cast<size_t>(GetMouseX() / ((float)GetScreenWidth() / _grid[0].size()));
    if (row < _grid.size() && col < _grid[0].size()) _grid[row][col] = 1;
  }

  if (IsKeyPressed(KEY_C)) [[unlikely]] {
    for (auto &row : _grid) std::fill(row.begin(), row.end(), 0);
  }
}
