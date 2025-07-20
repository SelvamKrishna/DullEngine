#include "render_system.hpp"

#include "../../vendor/raylib.h"

void RenderSystem::_drawNull() {
    BeginDrawing();
    EndDrawing();
}

void RenderSystem::_update() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(10, 10);
    EndDrawing();
}