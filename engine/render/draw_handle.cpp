#include "engine/render/draw_handle.hpp"

#include <vendor/raylib.h>
#include <vendor/zenutil/zen_prelude.hpp>

namespace dull::render {

    DrawHandle::DrawHandle()
    {
        rl::BeginDrawing();
        rl::ClearBackground(rl::BLACK);
        Z_ON_DBG { rl::DrawFPS(10, 10); }
    }

    DrawHandle::~DrawHandle() { rl::EndDrawing(); }

} // namespace dull::render
