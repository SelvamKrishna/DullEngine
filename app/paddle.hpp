#pragma once

#include <memory>
#include <string>
#include <utility>

#include "../source/core/app.hpp"
#include "../source/core/node.hpp"
#include "../source/utils/rect.hpp"
#include "ball.hpp"

class Paddle : public Node {
protected:
    Rect _rect = {0, (float)GetScreenHeight() / 2, 20, 100};
    float _speed = 500.0F;

    void _moveUp() { _rect.y = std::max<float>(_rect.y - (_speed * TIME_SYS.deltaTime()), 0); }

    void _moveDown() {
        _rect.y = std::min<float>(_rect.y + (_speed * TIME_SYS.deltaTime()),
                                  (float)GetScreenHeight() - _rect.height);
    }

public:
    explicit Paddle(std::string name) : Node(std::move(name)) {}
    ~Paddle() override = default;

    [[nodiscard]] bool isBallCollided(Ball &ball) {
        return CheckCollisionCircleRec(ball.pos(), ball.radius(), _rect);
    }

    [[nodiscard]] const Rect &rect() const { return _rect; }
};

class PlayerPaddle : public Paddle {
private:
    void _init() final;
    void _update() final;

public:
    explicit PlayerPaddle() : Paddle("PlayerPaddle") {}
    ~PlayerPaddle() override = default;
};

class AIPaddle : public Paddle {
private:
    std::weak_ptr<Ball> _ball_ref;

    void _init() final;
    void _update() final;

public:
    explicit AIPaddle() : Paddle("AIPaddle") {}
    ~AIPaddle() override = default;
};
