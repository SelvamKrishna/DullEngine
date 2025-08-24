#include "../source/core/app.hpp"
#include "../source/core/constants.hpp"

/// UPDATE: source/core/constants.hpp; GameInfo::*

int main(void) {
	auto& app = APP;
	SceneBuilder().pushToSystem(GameInfo::SceneID::Level0, true);

	app.run();
}