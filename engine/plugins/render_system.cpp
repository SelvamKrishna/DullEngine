#include "render_system.hpp"

#include "../../vendor/raylib.h"

void RenderSystem::_drawNull() noexcept {
	// Default draw null behaviour
	BeginDrawing();
	EndDrawing();
}

void RenderSystem::_update() {
	// Default draw behaviour
	BeginDrawing();
	ClearBackground(BLACK);
	DrawFPS(10, 10);
	EndDrawing();
}