#pragma once

#include "engine/util/vec2.hpp"

#include <vendor/zutils/tools.hpp>

#include <format>
#include <string>
#include <cstdint>

namespace dull::config {

/// --- Application Settings ---

constexpr std::string TITLE         = "Application";
constexpr util::Vec2i WINDOW_SIZE   = {800, 800};
constexpr bool        IS_VSYNC      = false;
constexpr bool        IS_RESIZEABLE = false;

constexpr uint32_t FIXED_PROCESS_FPS = 60;

/// --- Logging Settings ---

constexpr bool SHOULD_LOG_APP       = false;
constexpr bool SHOULD_LOG_SCENE_SYS = false;
constexpr bool SHOULD_LOG_LAYER_SYS = false;
constexpr bool SHOULD_LOG_EVENT_SYS = false;

/// --- Engine Config (DO NOT TOUCH) ---

constexpr uint32_t VER_MAJOR = 0;
constexpr uint32_t VER_MINOR = 1;

/// --- Utilities ---

[[nodiscard]]
inline std::string getVerString() noexcept
{
    return std::format("{}.{}", VER_MAJOR, VER_MINOR);
}

static inline void taskList() noexcept
{
    ZTODO("Better Scene managing");
    ZTODO("Better Layer creation");
    ZTODO("Proper render system plugin");
}

} // namespace dull::config
