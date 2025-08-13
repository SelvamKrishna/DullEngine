#pragma once

#include "gol_grid.hpp"
#include "../source/plugins/signal_system.hpp"
#include "../source/plugins/render_system.hpp"

#include <array>
#include <memory>
#include <string_view>

class CellRenderSystem : public RenderSystem {
private:
    static constexpr std::array<std::string_view, 5> HELP_UI_TEXT_LIST = {
        "Esc - Toggle UI",
        "Space - Pause Simulation",
        "LMB - Draw Cell",
        "C - Clear Fill Grid",
        "R - Random Fill Grid",
    };

    std::weak_ptr<CellGrid> _cell_grid_ref;
    std::shared_ptr<Observer> _observer;
    bool _show_help_ui = true;


    void _init() final;
    void _update() final;
};
