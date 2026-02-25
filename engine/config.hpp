#pragma once

#include <vendor/zutil/zutil.hpp>

#include <cstdint>
#include <format>
#include <string>

namespace dull::config {

inline constexpr uint8_t VERSION_MAJOR = 1;
inline constexpr uint8_t VERSION_MINOR = 0;

[[nodiscard]]
inline std::string GetVersionString() noexcept { return std::format("{}.{}", VERSION_MAJOR, VERSION_MINOR); }

inline constexpr uint32_t TICKS_PER_SECOND = 60;

inline const zutil::ProString DULL_TAG = {"[DULL]", zutil::ANSI::EX_Black};

} // namespace dull::config
