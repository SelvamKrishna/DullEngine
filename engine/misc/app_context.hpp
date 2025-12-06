#pragma once

#include "engine/util/vec2.hpp"

#include <string>

namespace dull::misc {

struct AppContext final {
    std::string title         = "Application";
    util::Vec2i window_size   = {800, 800};
    int         target_fps    = 0;
    bool        is_vsync      = false;
    bool        is_resizeable = false;
};

class AppContextBuilder final {
private:
    AppContext _app_ctx {};

public:
    explicit constexpr AppContextBuilder() = default;

#define _FN_BUILD(FN_INIT) \
    [[nodiscard]] constexpr AppContextBuilder& FN_INIT noexcept

    _FN_BUILD(setTitle(std::string new_title))
    {
        _app_ctx.title = std::move(new_title);
        return *this;
    }

    _FN_BUILD(setWindowSize(util::Vec2i new_size))
    {
        _app_ctx.window_size = new_size;
        return *this;
    }

    _FN_BUILD(setWindowWidth(float new_width))
    {
        _app_ctx.window_size.x = new_width;
        return *this;
    }

    _FN_BUILD(setWindowHeight(float new_height))
    {
        _app_ctx.window_size.y = new_height;
        return *this;
    }

    _FN_BUILD(setTargetFPS(int new_fps))
    {
        _app_ctx.target_fps = new_fps;
        return *this;
    }

    _FN_BUILD(maxTargetFPS())
    {
        _app_ctx.target_fps = 0;
        return *this;
    }

    _FN_BUILD(enableVsync())
    {
        _app_ctx.is_vsync = true;
        return *this;
    }

    _FN_BUILD(enableWindowResizing())
    {
        _app_ctx.is_resizeable = true;
        return *this;
    }

    _FN_BUILD(disableVsync())
    {
        _app_ctx.is_vsync = false;
        return *this;
    }

    _FN_BUILD(disableWindowResizing())
    {
        _app_ctx.is_resizeable = false;
        return *this;
    }

    [[nodiscard]]
    constexpr AppContext build() const noexcept { return _app_ctx; }

#undef _FN_BUILD
};

} // namespace dull::misc
