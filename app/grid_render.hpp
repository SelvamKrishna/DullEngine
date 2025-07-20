#pragma once

#include "../source/plugins/render_system.hpp"

#include "grid.hpp"

class GridRenderSystem : public RenderSystem {
private:
    Grid *_grid;

    void _update() final;

public:
    static GridRenderSystem &instance() {
        static GridRenderSystem instance;
        return instance;
    }

    void setGrid(Grid *grid) { _grid = grid; }
};
