#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/component/audio.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

class Node1 : public dull::process::Node {
private:
    dull::component::Music _music       {"assets/music1.mp3"};
    dull::component::Sound _click_sound {"assets/click.mp3"};

    void iStart() override {
        ZDBG("Hello World");
        is_fixed_process = false;
    }

    void iProcess() override {
        if (rl::IsKeyPressed(rl::KEY_SPACE)) _music->toggle();
        if (rl::IsKeyPressed(rl::KEY_ENTER)) _click_sound->play();
    }

public:
    Node1(std::string name) : Node {std::move(name)} {}
};

int main(void)
{
    dull::core::App app;

    DULL_CTX.audio_sys.setMasterVolume(0.5f);

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>(true, "Node1")
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayer(l1, true)
        .pushToBuffer();

    DULL_CTX.processor.setCurrentScene(sc1);
    app.run();
}
