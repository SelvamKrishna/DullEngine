#include <engine/config.hpp>
#include <engine/core/app.hpp>

#include <engine/misc/layer_builder.hpp>
#include <engine/misc/scene_builder.hpp>

int main(void)
{
    dull::core::App app;
    const dull::core::HandleContext& CTX = DULL_CTX;

    CTX.audio_sys.setMasterVolume(0.5f);

    dull::process::Layer::ID l1 = dull::misc::LayerBuilder{"Layer1"}
        .pushToBuffer();

    dull::process::Scene::ID sc1 = dull::misc::SceneBuilder{"Scene1"}
        .addLayer(l1, true)
        .pushToBuffer();

    CTX.processor.setCurrentScene(sc1);
    app.run();
}
