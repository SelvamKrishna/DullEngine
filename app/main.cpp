#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

class Node1 : public dull::process::Node {
private:
    dull::util::Music::ID _music;
    dull::util::Sound::ID _sound;

    void iStart() override {
        ZDBG("Hello World");

        is_process = true;
        is_fixed_process = false;
    }

    void iProcess() override {
        if (rl::IsKeyPressed(rl::KEY_SPACE)) {
            DULL_CTX.audio_sys.get(_music).toggle();
        }

        if (rl::IsKeyPressed(rl::KEY_ENTER)) {
            DULL_CTX.audio_sys.get(_sound).play();
        }
    }

public:
    Node1(std::string name, dull::util::Music::ID music, dull::util::Sound::ID sound)
    : Node {std::move(name)}
    , _music(music)
    , _sound(sound)
    {}
};

int main(void)
{
    dull::core::App app;

    DULL_CTX.audio_sys.setMasterVolume(0.5f);
    auto m1 = DULL_CTX.audio_sys.loadMusic("assets/music1.mp3");
    auto s1 = DULL_CTX.audio_sys.loadSound("assets/click.mp3");

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>(true, "Node1", m1, s1)
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayer(l1, true)
        .pushToBuffer();

    DULL_CTX.processor.setCurrentScene(sc1);

    app.run();
}
