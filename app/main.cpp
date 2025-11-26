#include "engine/core/app.hpp"

int main(void) {
  dull::core::App app {
    dull::misc::AppContextBuilder{}
      .setTitle("Hello World")
      .setWindowSize({500, 500})
      .build()
  };

  // return app.run();
  app.debug();
}
