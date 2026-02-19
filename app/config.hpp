#pragma once

#include <engine/process/i_processor.hpp>
#include <engine/util/window_context.hpp>

namespace app::config {

constexpr dull::util::WindowContext WINDOW_CONFIG {
    .title          = "Application",
    .dimension      = {800, 600},
    .isVsyncEnabled = false,
    .isResizeable   = false,
};

using Processor = dull::process::_VoidProcessor;

} // namespace app::config
