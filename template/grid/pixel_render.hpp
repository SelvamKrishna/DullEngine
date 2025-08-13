#if false
#pragma once

#include "../../source/core/app.hpp"
#include "../../source/plugins/render_system.hpp"
#include "pixel_grid.hpp"

#include <array>
#include <cstddef>
#include <memory>

/// CLASS: Render System used with PixelGrid
class PixelRenderer : public RenderSystem {
private:
    static constexpr std::array<ColorRGBA, 2> COLOR_TABLE = {
        ColorRGBA::black(), 
        ColorRGBA::white()
    };
    
    std::weak_ptr<PixelGrid> _pixel_grid_ref;

    void _init() final { _pixel_grid_ref = CURRENT_SCENE.getNode<PixelGrid>(); }

    void _update() final {
        BeginDrawing();
        ClearBackground(BLACK);

        if (auto pixel_grid = _pixel_grid_ref.lock()) {
            auto& window = pixel_grid->window();

            for (size_t x = 0; x < PixelGrid::width(); ++x) {
                for (size_t y = 0; y < PixelGrid::height(); ++y) {
                    const auto& PIXEL = window.at(x).at(y);
                    DrawRectangle(
                        static_cast<int>(x * GameInfo::Custom::PIXEL_SIZE),
                        static_cast<int>(y * GameInfo::Custom::PIXEL_SIZE),
                        GameInfo::Custom::PIXEL_SIZE,
                        GameInfo::Custom::PIXEL_SIZE,
                        COLOR_TABLE.at(static_cast<size_t>(PIXEL))
                    );
                }
            }
        }

        EndDrawing();
    }
};
#endif