#pragma once

#include "../source/plugins/render_system.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include <memory>

class PongRenderSystem : public RenderSystem {
private:
    std::weak_ptr<Paddle> _player_pad_ref;
    std::weak_ptr<Paddle> _ai_pad_ref;
    std::weak_ptr<Ball> _ball_ref;

    std::shared_ptr<Observer> _over_observer;

    void _init() final;
    void _update() final;
};