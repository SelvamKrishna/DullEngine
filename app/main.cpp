#include "../source/core/app.hpp"
#include "../source/core/node.hpp"

#include "grid.hpp"
#include "grid_render.hpp"

#include <memory>
#include <utility>

int main() {
    App &app = App::instance();
    app.init(800, 800, "Draw Grid - Sandbox");

    auto scene = std::make_unique<Scene>(1);
    scene->addNode(new Grid(24, 24));
    app.setCurrentScene(std::move(scene));

    auto render_sys = std::make_unique<GridRenderSystem>();
    render_sys->setGrid(app.currentScene().getNode<Grid>());
    app.setRenderSystem(std::move(render_sys));

    app.run();
}