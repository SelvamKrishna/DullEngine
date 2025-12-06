#include "engine/core/app.hpp"

int main(void)
{
    dull::core::App app = {
        {
            .title = "Hello World",
            .window_size = {500, 500},
        }
    };

    app.run();
}
