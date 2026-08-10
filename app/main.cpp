#include <engine/prelude.hpp>

int main(void)
{
    zen::logger::init(std::cout, std::cerr, zen::log_lvl::DBG, true);

    dull::core::Engine::Init({
        .title     {"Application"},
        .dimension {800, 600},
    });

    dull::core::Engine::Run({});
}
