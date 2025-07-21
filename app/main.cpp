#include "../source/core/app.hpp"
#include "../source/core/node.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "pong_render.hpp"

#include <memory>
#include <utility>

int main() {
    App &app = App::instance();
    app.init(800, 800, "Pong - Sandbox");

    auto scene = std::make_unique<Scene>(1);

    scene->addNode(new PlayerPaddle());
    scene->addNode(new AIPaddle());
    scene->addNode(new Ball());

    app.setCurrentScene(std::move(scene));

    auto *player = app.currentScene().getNode<PlayerPaddle>();
    auto *ai = app.currentScene().getNode<AIPaddle>();
    auto *ball = app.currentScene().getNode<Ball>();

    auto render_sys = std::make_unique<PongRenderSystem>(player, ai, ball);
    app.setRenderSystem(std::move(render_sys));

    app.run();
}