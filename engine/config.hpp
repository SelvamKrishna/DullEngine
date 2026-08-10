#pragma once

#include <zen/log.hpp>

#include <cstdint>
#include <format>
#include <string>

namespace dull::config {

    inline constexpr uint8_t VERSION_MAJOR {1};
    inline constexpr uint8_t VERSION_MINOR {0};

    inline constexpr uint32_t TICKS_PER_SECOND {30};

    inline const zen::log_tag DULL_TAG {"DULL", zen::ansi_color::BLUE};

    [[nodiscard]] inline std::string GetVersionString() noexcept
    {
        return std::format("{}.{}", VERSION_MAJOR, VERSION_MINOR);
    }

    [[nodiscard]] inline std::string GetConfigString() noexcept
    {
        return std::format("DullEngine - v{}.{}", VERSION_MAJOR, VERSION_MINOR);
    }

} // namespace dull::config
