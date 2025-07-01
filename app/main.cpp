#include "../source/core/app.hpp"
#include "../source/core/node.hpp"

int main() {
  App& app = App::instance();
  app.init(800, 800, "Test Window");

  Node* main_root = new Node("root");
  app.setRoot(main_root);
  app.run();
}
