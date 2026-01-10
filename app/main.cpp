#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

class Node1 : public dull::process::Node {
private:
    dull::util::Music::ID _music;

    void iStart() override {
        ZDBG("Hello World");

        is_process = true;
        is_fixed_process = false;
    }

    void iProcess() override {
        if (rl::IsKeyPressed(rl::KEY_SPACE)) {
            auto& music_ref = DULL_CTX.audio_sys.get(_music);
            if (music_ref.isPlaying()) music_ref.pause();
            else music_ref.play();
        }
    }

public:
    Node1(std::string name, dull::util::Music::ID music)
    : Node {std::move(name)}
    , _music(music)
    {}
};

int main(void)
{
    dull::core::App app;

    DULL_CTX.audio_sys.setMasterVolume(0.5f);
    auto m1 = DULL_CTX.audio_sys.loadMusic("C:\\dev\\DullEngine\\assets\\music1.mp3");

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>(true, "Node1", m1)
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayer(l1, true)
        .pushToBuffer();

    DULL_CTX.processor.setCurrentScene(sc1);

    app.run();
}
