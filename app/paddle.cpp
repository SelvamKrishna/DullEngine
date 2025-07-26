#include "paddle.hpp"
#include "ball.hpp"

#include "../source/core/app.hpp"
#include <memory>

void PlayerPaddle::_init() { _rect.x = 50; }

void PlayerPaddle::_update() {
    if (IsKeyDown(KEY_S)) {
        _moveDown();
    }
    if (IsKeyDown(KEY_W)) {
        _moveUp();
    }
}

void AIPaddle::_init() {
    _ball_ref = CURRENT_SCENE.getNode<Ball>();
    _rect.x = (float)GetScreenWidth() - 100;
}

void AIPaddle::_update() {
    if (auto ball = _ball_ref.lock()) {
        const float BALL_Y = ball->pos().y;
        const float PADDLE_CENTER = _rect.y + (_rect.height / 2.0F);
        const float REACTION_THRESHOLD = _rect.height / 4.0F;

        if (BALL_Y > PADDLE_CENTER + REACTION_THRESHOLD) {
            _moveDown();
        } else if (BALL_Y < PADDLE_CENTER - REACTION_THRESHOLD) {
            _moveUp();
        }
    }
}