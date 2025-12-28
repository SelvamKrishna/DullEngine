#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

void printTaskList() noexcept
{
    ZTODO("Proper render system plugin");
    ZTODO("Tree like node processing");
}

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
    printTaskList();

    dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>(true, "Node1")
        .pushToBuffer();

    dull::misc::SceneBuilder{"Scene1"}
        .addLayer("Layer1")
        .pushToBuffer();

    DULL_CTX.processor.setCurrentScene("Scene1");

    app.run();
}
