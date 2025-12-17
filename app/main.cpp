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
        {
            DULL_HANDLE.scene_sys.getLayerBuffer()
                .getLayer(getLayer())->getNodeHandle<Sample2>()
                .getNode()->setActive(true);
        }
    }

public:
    Sample() : dull::core::Node() {}
};

int main(void)
{
    dull::core::App app = { dull::core::AppContext::load() };
    dull::core::Handle& handle = app.getHandle();

    auto& layer_buf = handle.layer_buf;

    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main1"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main2"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main3"));

    layer_buf.getLayer("main1")->addNode("sample", std::make_unique<Sample>());
    layer_buf.getLayer("main1")->addNode("sample2", std::make_unique<Sample2>(), false);

    auto sc1 = std::make_unique<dull::core::Scene>();

    sc1->addLayer("main1");

    handle.scene_sys.getSceneBuffer().loadScene(dull::config::SceneID::Scene1, std::move(sc1));
    handle.scene_sys.setCurrentScene(dull::config::SceneID::Scene1);

    dull::config::taskList();

    handle.scene_sys.logStats();

    app.run();
}
