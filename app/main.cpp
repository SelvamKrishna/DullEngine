#include "engine/misc/app_builder.hpp"

int main(void) {
	auto& app = dull::misc::AppBuilder{}
    .setTitle("Example")
    .setWindowSize({500, 500})
    .build();

  app.run();
}
