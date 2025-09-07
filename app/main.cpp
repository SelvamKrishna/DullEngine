#include "engine/core/app.hpp"
#include "engine/core/constants.hpp"
#include "engine/utils/input.hpp"

/// A: UPDATE: engine/core/constants.hpp; GameInfo::*
/// B: Implement your own render system
/// C: Implement your own global system

int main(void) {
  auto &app = APP;
  SceneBuilder().pushToSystem(GameInfo::SceneID::Level0, true);

  Key(KeyCode::W).isDown();

  app.run();
}