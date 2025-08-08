#include "ball.hpp"

#include "../source/core/app.hpp"
#include "paddle.hpp"

#include <random>

void Ball::_init() {
    std::random_device rand_device;
    std::bernoulli_distribution rand_bool_dist(0.5F);
    std::mt19937 gen(rand_device());

    _direction = {.down = rand_bool_dist(gen), .right = rand_bool_dist(gen)};
    _pos = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
}

void Ball::_update() {
    const float MOVEMENT = _speed * TIME_SYS.deltaTime();
    const auto SCREEN_WIDTH = static_cast<float>(GetScreenWidth());
    const auto SCREEN_HEIGHT = static_cast<float>(GetScreenHeight());

    auto &scene = CURRENT_SCENE;

    if (_pos.y <= _radius || _pos.y >= SCREEN_HEIGHT - _radius) [[unlikely]] {
        _direction.down = !_direction.down;
    }

    if (scene.getNode<PlayerPaddle>().lock()->isBallCollided(*this) ||
        scene.getNode<AIPaddle>().lock()->isBallCollided(*this)) [[unlikely]] {
        _direction.right = !_direction.right; // Flip horizontal direction
    }

    if (_pos.x <= -_radius || _pos.x >= SCREEN_WIDTH + _radius) [[unlikely]] {
        _init();
        return;
    }

    _pos.x += _direction.right ? MOVEMENT : -MOVEMENT;
    _pos.y += _direction.down ? MOVEMENT : -MOVEMENT;
}