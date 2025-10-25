#include "engine/config.hpp"
#include "engine/misc/app_builder.hpp"

#include <iostream>

int main(void) {
	std::cout << dull::config::getVerString();

	dull::misc::AppBuilder{}
		.setTitle("Example")
		.setWindowDimension({500, 500})
		.enableVsync()
		.setTargetFPS(25)
		.enableWindowResizing()
		.buildAndRun();
}
