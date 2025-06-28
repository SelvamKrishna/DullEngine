#include "../source/core/app.hpp"
#include "../source/core/node.hpp"

int main() {
  App& app = App::Instance();
  app.Init(800, 800, "Test Window");

  Node* mainRoot = new Node("root");
  app.SetRoot(mainRoot);
  app.Run();
}
