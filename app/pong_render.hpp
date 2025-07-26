#pragma once

#include "../source/plugins/render_system.hpp"
#include "ball.hpp"
#include "paddle.hpp"

class PongRenderSystem : public RenderSystem {
private:
    Paddle *_player_pad;
    Paddle *_ai_pad;
    Ball *_ball;

    void _init() final;
    void _update() final;
};