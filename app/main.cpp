#include "../source/core/app.hpp"

#include "ball.hpp"
#include "paddle.hpp"
#include "pong_render.hpp"

#include <memory>

int main() {
    auto &app = App::instance();

    SceneBuilder(3)
        .addNode(std::make_unique<PlayerPaddle>())
        .addNode(std::make_unique<AIPaddle>())
        .addNode(std::make_unique<Ball>())
        .pushToSystem(GameInfo::SceneID::GAME, true);

    SceneBuilder(1).addNode(std::make_unique<PlayerPaddle>()).pushToSystem(GameInfo::SceneID::MENU);

    app.setRenderSystem(std::make_unique<PongRenderSystem>());
    app.run();
}