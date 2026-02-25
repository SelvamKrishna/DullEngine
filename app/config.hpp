#pragma once

#include <engine/core/i_processor.hpp>
#include <engine/util/window_context.hpp>

namespace app::config {

constexpr dull::util::WindowContext WINDOW_CONFIG {
    .title          = "Application",
    .dimension      = {800, 600},
    .isVsyncEnabled = false,
    .isResizeable   = false,
};

} // namespace app::config
