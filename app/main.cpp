#include "../source/core/app.hpp"

#include "gol_grid.hpp"
#include "gol_render.hpp"

#include <memory>

int main() {
    auto &app = App::instance();

    SceneBuilder(1)
        .addNode(std::make_unique<CellGrid>("cell_grid"))
        .pushToSystem(GameInfo::SceneID::Game, true);

    app.setRenderSystem(std::make_unique<CellRenderSystem>());
    app.run();
}