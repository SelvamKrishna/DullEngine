#include "engine/config.hpp"
#include "engine/core/app.hpp"

#include <iostream>

int main(void) {
	std::cout << dull::config::getVerString();

	dull::core::App {{ .title {"Unknown"} }}.run();

	return 0;
}