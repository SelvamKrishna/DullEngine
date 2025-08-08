#include "pong_render.hpp"

#include "../source/core/app.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include <memory>

void PongRenderSystem::_init() {
    _player_pad_ref = CURRENT_SCENE.getNode<PlayerPaddle>();
    _ai_pad_ref = CURRENT_SCENE.getNode<AIPaddle>();
    _ball_ref = CURRENT_SCENE.getNode<Ball>();

    _over_observer = std::make_shared<Observer>([this]() {
        _player_pad_ref = CURRENT_SCENE.getNode<PlayerPaddle>();
        _ai_pad_ref = CURRENT_SCENE.getNode<AIPaddle>();
        _ball_ref = CURRENT_SCENE.getNode<Ball>();
    });

    _over_observer->attachSignal("over");
}

void PongRenderSystem::_update() {
    BeginDrawing();
    ClearBackground(BLACK);

    if (auto player_pad = _player_pad_ref.lock()) {
        DrawRectangleRec(player_pad->rect(), WHITE);
    }

    if (auto ai_pad = _ai_pad_ref.lock()) {
        DrawRectangleRec(ai_pad->rect(), WHITE);
    }

    if (auto ball = _ball_ref.lock()) {
        DrawCircleV(_ball_ref.lock()->pos(), _ball_ref.lock()->radius(), WHITE);
    }

    DrawFPS(10, 10);
    EndDrawing();
}