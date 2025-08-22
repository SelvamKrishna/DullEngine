#pragma once

#include "../utils/color.hpp"

#include <cstdint>

namespace GameInfo {
    inline constexpr const char* TITLE = "Game Of Life - Sandbox";

    inline constexpr int WINDOW_WIDTH  = 800;
    inline constexpr int WINDOW_HEIGHT = 800;

    inline constexpr float FIXED_FRAME_RATE = 10.0F;

    inline constexpr uint8_t TOTAL_SCENE_COUNT = 1;
    enum class SceneID : uint8_t {
        Game,
    };

    namespace Custom {
        inline constexpr uint8_t PIXEL_SIZE = 8;

        inline constexpr ColorRGBA ALIVE_COLOR = ColorRGBA::white();
        inline constexpr ColorRGBA DEAD_COLOR  = ColorRGBA::black();
    }
}