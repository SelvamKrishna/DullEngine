#pragma once

#include <format>
#include <string>
#include <cstdint>

namespace dull::config {

#ifdef NDEBUG
constexpr bool IS_DEBUG_BUILD = false;
#else
constexpr bool IS_DEBUG_BUILD = true;
#endif

constexpr uint32_t VER_MAJOR = 0;
constexpr uint32_t VER_MINOR = 1;

[[nodiscard]] inline std::string getVerString() noexcept {
  return std::format("{}.{}", VER_MAJOR, VER_MINOR);
}

constexpr bool SHOULD_LOG_APP       = true;
constexpr bool SHOULD_LOG_EVENT_SYS = true;
constexpr bool SHOULD_LOG_SCENE_SYS = true;

} // namespace dull::config
