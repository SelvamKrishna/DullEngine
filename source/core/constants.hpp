#pragma once

#include "../utils/color.hpp"

#include <cstddef>
#include <cstdint>

/// MODIFY:
namespace GameInfo {
#define TITLE "Game Of Life - Sandbox"

static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 800;

static constexpr float FIXED_FRAME_RATE = 10.0F;

static constexpr size_t TOTAL_SCENE_COUNT = 1;
enum class SceneID : uint8_t {
    Game,
};

namespace Custom {
static constexpr uint8_t PIXEL_SIZE = 8;

static constexpr ColorRGBA ALIVE_COLOR = ColorRGBA::black();
static constexpr ColorRGBA DEAD_COLOR = ColorRGBA::white();
}; // namespace Custom

}; // namespace GameInfo