#include <engine/config.hpp>
#include <engine/core/engine.hpp>

int main(void)
{
    dull::core::Engine _ {};

    dull::core::Engine::Init({
        .title          {"Application"},
        .dimension      {600, 600},
        .isVsync        = false,
        .isResizeable   = false,
    });

    dull::core::Engine::Run({});
}
