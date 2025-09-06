#include "engine/core/app.hpp"
#include "engine/core/constants.hpp"

/// A: UPDATE: engine/core/constants.hpp; GameInfo::*
/// B: Implement your own render system

int main(void) {
  auto &app = APP;
  SceneBuilder().pushToSystem(GameInfo::SceneID::Level0, true);

  app.run();
}