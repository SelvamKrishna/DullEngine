#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

class Node1 : public dull::process::Node {
    void iStart() override {
        ZDBG("Hllo World");

        is_process = false;
        is_fixed_process = false;
    }

    void iProcess() override { ZDBG("Hello Procees"); }

public:
    Node1(std::string name) : Node {std::move(name)} {}
};

int main(void)
{
    dull::core::App app;

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>(true, "Node1")
        .pushToBuffer();

    dull::process::Layer::ID l2 = dull::misc::LayerBuilder{"Layer2"}
        .addNode<Node1>(true, "Node1")
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayers({
            {l1, true},
            {l2, true},
        })
        .pushToBuffer();

    DULL_CTX.processor.setCurrentScene(sc1);

    app.run();
}
