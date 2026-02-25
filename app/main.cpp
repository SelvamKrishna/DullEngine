#include "app/config.hpp"

#include <engine/core/app.hpp>

int main(void)
{
    dull::core::App app;
    dull::core::App::Init(app::config::WINDOW_CONFIG);
    dull::core::App::Run(nullptr);
}
