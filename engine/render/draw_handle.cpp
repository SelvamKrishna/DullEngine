#include "engine/render/draw_handle.hpp"

#include <vendor/raylib.h>

namespace dull::render {

    DrawHandle::DrawHandle()
    {
        rl::BeginDrawing();
        rl::ClearBackground(rl::BLACK);
    }

    DrawHandle::~DrawHandle()
    {
        rl::EndDrawing();
    }

} // namespace dull::render
