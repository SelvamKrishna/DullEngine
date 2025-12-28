#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>

void printTaskList() noexcept
{
    ZTODO("Better Layer creation");
    ZTODO("Better Scene creation");
    ZTODO("Proper render system plugin");
}

class Node1 : public dull::process::Node {
    void iStart() override {
        ZDBG("Hllo World");

        is_process = false;
        is_fixed_process = false;
    }

    void iProcess() override { ZDBG("Hello Procees"); }

public:
    Node1(std::string name) : dull::process::Node {std::move(name)} {}
};

int main(void)
{
    dull::core::App app;
    printTaskList();

    dull::misc::LayerBuilder{"Layer1"}
        .addNode<Node1>(true, "Node1")
        .pushToBuffer();


    auto s1 = std::make_unique<dull::process::Scene>("sc1");
    s1->addLayer("Layer1");

    dull::process::World::getSceneBuffer().loadData("sc1", std::move(s1));
    DULL_CTX.processor.setCurrentScene("sc1");

    app.run();
}
