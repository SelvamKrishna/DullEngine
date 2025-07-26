#include "pong_render.hpp"

#include "../source/core/app.hpp"
#include "ball.hpp"
#include "paddle.hpp"

void PongRenderSystem::_init() {
    _player_pad = CURRENT_SCENE.getNode<PlayerPaddle>();
    _ai_pad = CURRENT_SCENE.getNode<AIPaddle>();
    _ball = CURRENT_SCENE.getNode<Ball>();
}

void PongRenderSystem::_update() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawRectangleRec(_player_pad->rect(), WHITE);
    DrawRectangleRec(_ai_pad->rect(), WHITE);
    DrawCircleV(_ball->pos(), _ball->radius(), WHITE);
    EndDrawing();
}