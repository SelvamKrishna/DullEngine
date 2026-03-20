#include <engine/core/engine.hpp>
#include <engine/config.hpp>

#include <engine/util/direct_processor.hpp>

int main(void)
{
    dull::core::Engine _ {};

    dull::core::Engine::Init({
        .title          = "Application",
        .dimension      = {800, 600},
        .isVsync        = false,
        .isResizeable   = false,
    });

    zen::core::Log(zen::core::DBG, {"DullEngine-{}", dull::config::GetVersionString()});

    dull::core::Engine::Run();
}
