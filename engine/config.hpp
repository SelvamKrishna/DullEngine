#pragma once

#include <format>
#include <string>
#include <cstdint>

namespace dull::config {

/// --- Build Settings ---

#ifdef NDEBUG
constexpr bool IS_DEBUG_BUILD = false;
#else
constexpr bool IS_DEBUG_BUILD = true;
#endif

constexpr uint32_t VER_MAJOR = 0;
constexpr uint32_t VER_MINOR = 1;

/// --- Logging Settings ---

constexpr bool SHOULD_LOG_APP       = true;
constexpr bool SHOULD_LOG_EVENT_SYS = true;
constexpr bool SHOULD_LOG_SCENE_SYS = true;

/// --- Utilities ---

[[nodiscard]] inline std::string getVerString() noexcept {
  return std::format("{}.{}", VER_MAJOR, VER_MINOR);
}

} // namespace dull::config
