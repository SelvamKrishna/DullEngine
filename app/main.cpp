#include "../source/core/app.hpp"
#include "../source/core/node.hpp"

#include "ball.hpp"
#include "paddle.hpp"
#include "pong_render.hpp"

#include <memory>

int main() {
    App &app = App::instance();
    app.init(800, 800, "Pong - Sandbox");
    app.setCurrentScene(std::make_unique<Scene>());

    auto &scene = CURRENT_SCENE;

    scene.addNode(std::make_unique<PlayerPaddle>());
    scene.addNode(std::make_unique<AIPaddle>());
    scene.addNode(std::make_unique<Ball>());

    app.setRenderSystem(std::make_unique<PongRenderSystem>());

    app.run();
}