#include <engine/core/app.hpp>

int main(void)
{
    dull::core::App app {
        {},
        {
            .title = "Test Application",
            .dimension = {500, 500},
        }
    };

    app.Run();
}
