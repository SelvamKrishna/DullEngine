#include "../source/core/app.hpp"
#include "../source/core/node.hpp"

#include "../source/plugins/audio_system.hpp"

#include "ball.hpp"
#include "paddle.hpp"
#include "pong_render.hpp"

#include <memory>
#include <utility>

int main() {
    App &app = App::instance();
    app.init(800, 800, "Pong - Sandbox");

    auto scene = std::make_unique<Scene>(3);

    scene->addNode(new PlayerPaddle());
    scene->addNode(new AIPaddle());
    scene->addNode(new Ball());

    app.setCurrentScene(std::move(scene));
    app.setRenderSystem(std::move(std::make_unique<PongRenderSystem>()));

    app.run();
}