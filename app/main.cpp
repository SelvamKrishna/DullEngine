#include <engine/core/app.hpp>
#include <engine/core/scene.hpp>

class Sample : public dull::core::Node {
    void _start() final {
        ZDBG("Started");
    }

    void _update() final {
    }

public:
    Sample() : dull::core::Node("Hello") {}
};

int main(void)
{
    dull::core::App app = {
        {
            .title = "Hello World",
            .window_size = {500, 500},
        }
    };

    dull::core::Handle& handle = app.handle();
    auto& layer_buf = handle.sceneSystem().getLayerBuffer();

    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main1"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main2"));
    layer_buf.loadLayer(std::make_unique<dull::core::Layer>("main3"));
    layer_buf.getLayer("main1")->addNode(std::make_unique<Sample>());

    dull::core::Scene scene1 {"main1", "main2", "main3"};
    handle.sceneSystem().setCurrentScene(scene1);

    app.run();
}
