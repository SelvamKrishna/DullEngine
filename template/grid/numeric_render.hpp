#ifdef false

#include "../../source/core/app.hpp"
#include "../../source/plugins/render_system.hpp"
#include "numeric_grid.hpp"

#include <array>
#include <cstddef>
#include <memory>

/// CLASS: Render System used with NumericGrid
/// MODIFY: all(*); COLOR_TABLE; Grid; _update;
class NumericGridRender : public RenderSystem {
private:
    using Grid = NumericGrid;

    static constexpr std::array<ColorRGBA, 2> COLOR_TABLE = {ColorRGBA::black(), ColorRGBA::white()};
    std::weak_ptr<Grid> _cell_grid_ref;

    void _init() final { _cell_grid_ref = CURRENT_SCENE.getNode<Grid>(); }

    void _update() final {
        BeginDrawing();
        ClearBackground(BLACK);

        if (auto cell_grid = _cell_grid_ref.lock()) {
            auto &grid = cell_grid->grid();

            for (size_t x = 0; x < Grid::colCount(); ++x) {
                for (size_t y = 0; y < Grid::rowCount(); ++y) {
                    const auto &cell = grid.at(x).at(y);
                    DrawRectangle(static_cast<int>(x * GameInfo::Custom::PIXEL_SIZE),
                                  static_cast<int>(y * GameInfo::Custom::PIXEL_SIZE),
                                  GameInfo::Custom::PIXEL_SIZE,
                                  GameInfo::Custom::PIXEL_SIZE,
                                  COLOR_TABLE.at(static_cast<size_t>(cell)));
                }
            }
        }

        DrawFPS(10, 10);
        EndDrawing();
    }
};

#endif