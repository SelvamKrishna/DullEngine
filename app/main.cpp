#include "engine/misc/app_builder.hpp"

int main(void) {
	dull::misc::AppBuilder {}
		.setTitle("Example")
		.setWindowSize({500, 500})
		.buildAndRun();
}
