#pragma once

#include "../source/plugins/render_system.hpp"
#include "ball.hpp"
#include "paddle.hpp"

class PongRenderSystem : public RenderSystem {
private:
    Paddle *_player_pad;
    Paddle *_ai_pad;
    Ball *_ball;

    void _update() final;

public:
    PongRenderSystem(Paddle *player_pad, Paddle *ai_pad, Ball *ball)
        : _player_pad(player_pad), _ai_pad(ai_pad), _ball(ball) {}
};