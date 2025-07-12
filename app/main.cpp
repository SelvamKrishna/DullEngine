#include "../source/core/app.hpp"
#include "../source/core/node.hpp"
#include "grid_render.hpp"

int main() {
  App& app = App::instance();
  app.init(800, 800, "Test Window");

  app.setCurrentScene(new Scene(0));
  app.setRenderSystem(&GridRenderSystem::instance());

  app.run();
}
