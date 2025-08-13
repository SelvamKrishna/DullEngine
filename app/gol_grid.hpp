#pragma once

#include "../source/core/constants.hpp"
#include "../source/core/node.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

enum class CellState : uint8_t {
    Alive, // 1 -> 1
    Dead,  // 0 -> 0
    Birth, // 0 -> 1
    Dying, // 1 -> 0
};

class CellGrid : public Node {
public:
    static constexpr size_t COL_COUNT = GameInfo::WINDOW_HEIGHT / GameInfo::Custom::PIXEL_SIZE;
    static constexpr size_t ROW_COUNT = GameInfo::WINDOW_WIDTH  / GameInfo::Custom::PIXEL_SIZE;

private:
    using CellArray2D = std::array<std::array<CellState, ROW_COUNT>, COL_COUNT>;

    bool _simulate = true;
    CellArray2D _grid;

    [[nodiscard]] uint8_t _countNeighbours(size_t x, size_t y) const noexcept;
    void _fillRandom() noexcept;
    void _fillEmpty() noexcept;

protected:
    void _init() final;
    void _update() final;
    void _fixedUpdate() final;

public:
    explicit CellGrid(std::string name) : Node(std::move(name)) {}
    ~CellGrid() override = default;

    [[nodiscard]] constexpr CellArray2D& grid() noexcept { return _grid; }
};