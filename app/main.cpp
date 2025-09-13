#include "engine/core/app.hpp"
#include "app/constants.hpp"

/// A: UPDATE: app/constants.hpp; GameInfo::*
/// B: Implement your own render system
/// C: Implement your own physics system
/// D: Implement your own nodes

int main(void) {
	auto &app = APP;

	SceneBuilder{}
		.newScene()
		.pushToSystem(GameInfo::SceneID::Level0, true);

	app.run();
}