#pragma once

#include "../source/plugins/render_system.hpp"
#include "gol_grid.hpp"
#include <memory>

class CellRenderSystem : public RenderSystem {
private:
    std::weak_ptr<CellGrid> _cell_grid_ref;

    void _init() final;
    void _update() final;
};