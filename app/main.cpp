#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

struct KeyEvent { int key_code; };

class Node1 : public dull::process::Node {
private:
    dull::misc::EventListener<KeyEvent>::ID key_event_listener;

    void iStart() override {
        is_fixed_process = false;

        key_event_listener = DULL_CTX.event_sys.getChannel<KeyEvent>()
            .subscribe(
                [](const KeyEvent& event) { ZINFO("Key Event received! Key Code: {}", event.key_code); },
                {"node1-key-event-listener"}
            );
    }

    void iProcess() override {
        if (rl::IsKeyPressed(rl::KEY_W)) [[unlikely]] {
            dull::system::EventSystem& event_sys = DULL_CTX.event_sys;
            event_sys.emit<KeyEvent>({42});
        }

        if (rl::IsKeyPressed(rl::KEY_S)) [[unlikely]] {
            DULL_CTX.event_sys.getChannel<KeyEvent>().unsubscribe(key_event_listener);
            key_event_listener = {0};
        }
    }

public:
    explicit Node1(std::string name) : dull::process::Node {name} {}

    ~Node1() override {
    }
};

int main(void)
{
    dull::core::App app;
    const dull::core::HandleContext& CTX = DULL_CTX;

    CTX.audio_sys.setMasterVolume(0.5f);

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>("Node1")
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayer(l1, true)
        .pushToBuffer();

    CTX.processor.setCurrentScene(sc1);
    app.run();
}
