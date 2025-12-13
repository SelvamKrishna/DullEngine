#include <engine/config.hpp>
#include <engine/core/app.hpp>
#include <engine/core/scene.hpp>

class Sample : public dull::core::Node {
    void _start() final {
        ZDBG("Started");
    }

    void _update() final {
    }

public:
    Sample() : dull::core::Node() {}
};

int main(void)
{
    dull::core::App app = { dull::core::AppContext::load() };

    dull::core::Handle& handle = app.getHandle();
    auto& layer_buf = handle.sceneSystem().getLayerBuffer();

    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main1"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main2"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main3"));
    layer_buf.getLayer("main1")->addNode("sample", std::make_unique<Sample>());

    dull::core::Scene scene1 {"main1", "main2", "main3"};
    handle.sceneSystem().current_scene = scene1;

    dull::config::taskList();
    app.run();
}
