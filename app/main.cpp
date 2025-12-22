#include <engine/config.hpp>
#include <engine/core/app.hpp>

int main(void)
{
    dull::core::App app = { dull::core::AppContext {} };

    const auto& DULL = app.getHandle().ctx;

    DULL.processor.getSceneBuffer().loadScene(std::make_unique<dull::core::Scene>("Scene1"));
    DULL.processor.setCurrentScene("Scene1");

    app.run();
}
