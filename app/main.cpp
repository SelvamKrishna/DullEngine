#include "../source/core/app.hpp"
#include "../source/core/node.hpp"
#include "grid.hpp"
#include "grid_render.hpp"

int main() {
  App& app = App::instance();
  app.init(800, 800, "Test Window");

  Scene* scene = new Scene(0);
  scene->addNode(new Grid(100, 100));
  app.setCurrentScene(scene);

  GridRenderSystem& gridRenderSystem = GridRenderSystem::instance();
  gridRenderSystem.setGrid(dynamic_cast<Grid*>(scene->getNodeByType<Grid>()));
  app.setRenderSystem(&gridRenderSystem);

  app.run();
}
