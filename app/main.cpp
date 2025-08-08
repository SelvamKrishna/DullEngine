#include "../source/core/app.hpp"
#include "../source/core/node.hpp"

#include "ball.hpp"
#include "paddle.hpp"
#include "pong_render.hpp"

#include <memory>

int main() {
    App &app = App::instance();
    app.init();

    auto game_scene = std::make_unique<Scene>();
    auto menu_scene = std::make_unique<Scene>();

    game_scene->addNode(std::make_unique<PlayerPaddle>());
    game_scene->addNode(std::make_unique<AIPaddle>());
    game_scene->addNode(std::make_unique<Ball>());

    menu_scene->addNode(std::make_unique<PlayerPaddle>());

    SCENE_SYS.addScene(SceneID::GAME, std::move(game_scene));
    SCENE_SYS.addScene(SceneID::MENU, std::move(menu_scene));

    SCENE_SYS.setCurrent(SceneID::GAME);

    app.setRenderSystem(std::make_unique<PongRenderSystem>());

    app.run();
}