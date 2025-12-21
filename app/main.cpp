#include <engine/config.hpp>
#include <engine/core/app.hpp>
#include <engine/core/scene.hpp>

int main(void)
{
    dull::core::App app = { dull::core::AppContext {} };
    app.run();
}
