#pragma once

#include <vendor/zutil/zutil.hpp>

#include <cstdint>

namespace dull::config {

inline const zutil::ProString DULL_TAG = {"[DULL]", zutil::ANSI::EX_Black};

inline constexpr uint32_t TICKS_PER_SECOND = 60;

} // namespace dull::config
