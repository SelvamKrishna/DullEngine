#pragma once

#include <string>

#include "../source/core/node.hpp"
#include "../source/utils/vec2.hpp"

class Ball : public Node {
    friend class PongRenderSystem;

protected:
    float _radius = 20.0F;
    Vec2 _pos = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    float _speed = 250.0F;

    struct Direction {
        bool down;
        bool right;
    } _direction;

    void _init() final;
    void _update() final;

public:
    explicit Ball() : Node("Ball") {}
    ~Ball() override = default;

    [[nodiscard]] const Vec2 &pos() const { return _pos; }
    [[nodiscard]] float radius() const { return _radius; }
};