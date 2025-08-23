#pragma once

#include <cstdint>
#include "../utils/vec2.hpp"

namespace GameInfo {
    inline constexpr const char* TITLE = "Game Of Life - Sandbox";

    inline constexpr int WINDOW_WIDTH  = 800;
    inline constexpr int WINDOW_HEIGHT = 800;

    inline constexpr float FIXED_FRAME_RATE = 10.0F;

    inline constexpr uint8_t TOTAL_SCENE_COUNT = 1;
    enum class SceneID : uint8_t {
        MainScene,
    };

    namespace Custom {
        inline constexpr uint8_t INPUT_PANEL_ROWS = 4;
        inline constexpr uint8_t INPUT_PANEL_COLS = 4;
        inline constexpr uint8_t TOTAL_INPUT = INPUT_PANEL_ROWS * INPUT_PANEL_COLS;

        constexpr int SWITCH_SPACING = 48;
        constexpr int SWITCH_SIZE = 24;
        constexpr Vec2i SWITCH_OFFSET = {50, 50};

        constexpr int PANEL_SPACING = 48;
        constexpr int PANEL_SIZE = 24;
        constexpr Vec2i PANEL_OFFSET = {300, 50};

        constexpr Vec2i BIAS_COORD = {4, 4};
    }
}