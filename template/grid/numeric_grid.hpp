#ifdef false

#include "../../source/core/constants.hpp"
#include "../../source/core/node.hpp"

#include <array>
#include <cstddef>
#include <string>

/// MODIFY: All the variants of cells
enum class CellState : uint8_t {
    Alive,
    Dead,
};

/// CLASS: Fixed sized 2D array node
/// MODIFY: all(*); 'source/core/constants.hpp' for GameInfo::*;
class NumericGrid : public Node {
private:
    static constexpr size_t COL_COUNT = GameInfo::WINDOW_HEIGHT / GameInfo::Custom::PIXEL_SIZE;
    static constexpr size_t ROW_COUNT = GameInfo::WINDOW_WIDTH / GameInfo::Custom::PIXEL_SIZE;
    using CellArray = std::array<std::array<CellState, ROW_COUNT>, COL_COUNT>;

    CellArray _grid;

protected:
    void _init() override;
    void _update() override;
    void _fixedUpdate() override;

public:
    explicit NumericGrid(std::string name) : Node(std::move(name)) {}
    ~NumericGrid() override = default;

    [[nodiscard]] static constexpr size_t colCount() noexcept { return COL_COUNT; }
    [[nodiscard]] static constexpr size_t rowCount() noexcept { return ROW_COUNT; }
    [[nodiscard]] constexpr CellArray &grid() noexcept { return _grid; }
};

/// CLASS: Templated 2D array node
template <size_t ColCount, size_t RowCount> class DynamicNumericGrid : public Node {
private:
    using CellArray = std::array<std::array<CellState, RowCount>, ColCount>;

    CellArray _grid;

protected:
    void _init() override;
    void _update() override;
    void _fixedUpdate() override;

public:
    explicit DynamicNumericGrid(std::string name) : Node(std::move(name)) {}
    ~DynamicNumericGrid() override = default;

    [[nodiscard]] static constexpr size_t colCount() noexcept { return ColCount; }
    [[nodiscard]] static constexpr size_t rowCount() noexcept { return RowCount; }
    [[nodiscard]] constexpr CellArray &grid() noexcept { return _grid; }
};

#endif