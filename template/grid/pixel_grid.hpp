#if false
#pragma once

#include "../../source/core/constants.hpp"
#include "../../source/core/node.hpp"

#include <array>
#include <cstddef>
#include <string>

/// MODIFY: All the variants of the pixel
enum PixelType : uint8_t { Alive, Dead };

/// CLASS: Static sized 2D pixel array
/// MODIFY: 'source/core/constants.hpp' for GameInfo::*;
class PixelGrid : public Node {
private:
    static constexpr size_t COL_COUNT = GameInfo::WINDOW_HEIGHT / GameInfo::Custom::PIXEL_SIZE;
    static constexpr size_t ROW_COUNT = GameInfo::WINDOW_WIDTH / GameInfo::Custom::PIXEL_SIZE;
    using PixelWindow = std::array<std::array<PixelType, ROW_COUNT>, COL_COUNT>;

    PixelWindow _window;

protected:
    void _init() override;
    void _update() override;
    void _fixedUpdate() override;

public:
    explicit PixelGrid(std::string name) : Node(std::move(name)) {}
    ~PixelGrid() override = default;

    [[nodiscard]] static constexpr size_t width() noexcept { return COL_COUNT; }
    [[nodiscard]] static constexpr size_t height() noexcept { return ROW_COUNT; }
    [[nodiscard]] constexpr PixelWindow& window() noexcept { return _window; }
};

/// CLASS: Templated 2D array node
template <size_t ColCount, size_t RowCount> class PixelGridMeta : public Node {
private:
    using PixelWindow = std::array<std::array<PixelType, RowCount>, ColCount>;
    PixelWindow _window;

protected:
    void _init() override;
    void _update() override;
    void _fixedUpdate() override;

public:
    explicit PixelGridMeta(std::string name) : Node(std::move(name)) {}
    ~PixelGridMeta() override = default;

    [[nodiscard]] static constexpr size_t width() noexcept { return ColCount; }
    [[nodiscard]] static constexpr size_t height() noexcept { return RowCount; }
    [[nodiscard]] constexpr PixelWindow& window() noexcept { return _window; }
};
#endif