#include "../source/core/app.hpp"
#include "input_handler.hpp"
#include "perceptron.hpp"
#include "perceptron_renderer.hpp"
#include <memory>

int main(void) {
    auto& app = App::instance();

    SceneBuilder()
        .addNode(std::make_unique<Perceptron>("perceptron"))
        .addNode(std::make_unique<InputHandler>("input-handler"))
        .pushToSystem(GameInfo::SceneID::MainScene, true);

    app.setRenderSystem(std::make_unique<PerceptronRenderer>());
    app.run();
}