#pragma once

#include <cstdint>
#include <vector>

#include "../source/core/node.hpp"

class Grid : public Node {
private:
  std::vector<std::pmr::vector<uint8_t>> _grid;

public:
  Grid(uint8_t rows = 10, uint8_t cols = 10);
  ~Grid();

private:
  void _init() final;
  void _update() final;

public:
  uint8_t getWidth() const { return _grid.empty() ? 0 : static_cast<uint8_t>(_grid[0].size()); }
  uint8_t getHeight() const { return static_cast<uint8_t>(_grid.size()); }

  uint8_t getCell(size_t row, size_t col) const {
    if (row < _grid.size() && col < _grid[0].size()) { return _grid[row][col]; }
    return 0;
  }
};