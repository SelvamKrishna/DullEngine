#pragma once

#include <vendor/zutils/tools.hpp>

#include <format>
#include <string>
#include <cstdint>

namespace dull::config {

/// --- Engine Config (DO NOT TOUCH) ---

constexpr uint32_t VER_MAJOR = 0;
constexpr uint32_t VER_MINOR = 1;

/// --- Logging Settings ---

constexpr bool SHOULD_LOG_APP       = false;
constexpr bool SHOULD_LOG_EVENT_SYS = false;
constexpr bool SHOULD_LOG_SCENE_SYS = false;

/// --- Application Settings ---

constexpr uint32_t FIXED_PROCESS_FPS = 60;

/// --- Utilities ---

[[nodiscard]]
inline std::string getVerString() noexcept
{
    return std::format("{}.{}", VER_MAJOR, VER_MINOR);
}

static inline void taskList() noexcept
{
    ZTODO("Handle to provide restricted controls and access to inner systems");
    ZTODO("Proper segregation of classes and logic into files");
    ZTODO("Proper render system plugin");
    ZTODO("Push layer into layer buffer");
}

} // namespace dull::config
