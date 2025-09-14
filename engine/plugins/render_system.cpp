#include "engine/plugins/render_system.hpp"

#include "vendor/raylib.h"

void RenderSystem::_drawNull() noexcept {
	// Default draw null behaviour
	BeginDrawing();
	EndDrawing();
}

void RenderSystem::_update() {
	BeginDrawing();
	_draw();
	EndDrawing();
}