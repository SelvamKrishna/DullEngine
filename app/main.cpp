#include <engine/prelude.hpp>

int main(void)
{
    dull::core::Engine::Init({
        .title     {"Application"},
        .dimension {800, 600},
    });

    dull::core::Engine::Run({});
}
