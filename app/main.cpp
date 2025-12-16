#include <engine/config.hpp>
#include <engine/core/app.hpp>
#include <engine/core/scene.hpp>

class Sample2 : public dull::core::Node {
private:
    void _start() final { ZDBG("Node: Started Sample 2"); }
    void _update() final { }

public:
    Sample2() : dull::core::Node() {}
};

class Sample : public dull::core::Node {
private:
    void _start() final { ZDBG("Node: Started Sample 1"); }
    void _update() final
    {
        if (rl::IsKeyPressed(rl::KEY_B))
            DULL_HANDLE.scene_sys->getLayerBuffer()
                .getLayer(getOwnerLayer())->getNodeHandle<Sample2>()
                .getNode()->setActive(true);
    }

public:
    Sample() : dull::core::Node() {}
};

int main(void)
{
    dull::core::App app = { dull::core::AppContext::load() };
    dull::core::Handle& handle = app.getHandle();

    auto& layer_buf = handle.scene_sys->getLayerBuffer();

    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main1"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main2"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main3"));

    layer_buf.getLayer("main1")->addNode("sample", std::make_unique<Sample>());
    layer_buf.getLayer("main1")->addNode("sample2", std::make_unique<Sample2>(), false);

    handle.scene_sys->current_scene = dull::core::Scene {"main1", "main2", "main3"};

    dull::config::taskList();
    layer_buf.logStats();

    app.run();
}
