#pragma once

#include <cstddef>
#include <cstdint>

namespace GameInfo {
#define TITLE "Pong-Sandbox"

static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 800;

static constexpr size_t TOTAL_SCENE_COUNT = 2;
enum class SceneID : uint8_t {
    GAME,
    MENU,
};
}; // namespace GameInfo