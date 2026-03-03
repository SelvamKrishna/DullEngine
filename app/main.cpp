#include <engine/core/app.hpp>

int main(void)
{
    dull::core::App app;

    dull::core::App::Init({
        .title          = "Application",
        .dimension      = {800, 600},
        .isVsyncEnabled = false,
        .isResizeable   = false,
    });

    dull::core::App::Run();
}
