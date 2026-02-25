#pragma once

#include "engine/util/vec2.hpp"

#include <string>

namespace dull::util {

// ---
// Window configuration
// ---
struct WindowContext final {
    std::string title;
    util::Vec2i dimension;
    bool        isVsyncEnabled;
    bool        isResizeable;
};

} // namespace dull::util
