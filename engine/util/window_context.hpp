#pragma once

#include "engine/config.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zenutil/zen_prelude.hpp>

#include <string>

namespace dull::util {

    struct WindowContext final {
        std::string title          = config::GetConfigString();
        util::Vec2i dimension      = {640, 640};
        bool        isVsyncEnabled = false;
        bool        isResizeable   = false;
    };

} // namespace dull::util
