
#include "pong_render.hpp"

void PongRenderSystem::_update() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(_player_pad->rect(), WHITE);
    DrawRectangleRec(_ai_pad->rect(), WHITE);
    DrawCircleV(_ball->pos(), _ball->radius(), WHITE);
    EndDrawing();
}