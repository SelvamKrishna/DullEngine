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

  #define BUILDER_FN(FN_INIT) \
    [[nodiscard]] constexpr AppContextBuilder& FN_INIT noexcept

  BUILDER_FN(setTitle(std::string new_title)) {
    _app_ctx.title = std::move(new_title);
    return *this;
  }

  BUILDER_FN(setWindowSize(util::Vec2i new_size)) {
    _app_ctx.window_size = new_size;
    return *this;
  }

  BUILDER_FN(setWindowWidth(float new_width)) {
    _app_ctx.window_size.x = new_width;
    return *this;
  }

  BUILDER_FN(setWindowHeight(float new_height)) {
    _app_ctx.window_size.y = new_height;
    return *this;
  }

  BUILDER_FN(setTargetFPS(int new_fps)) {
    _app_ctx.target_fps = new_fps;
    return *this;
  }

  BUILDER_FN(maxTargetFPS()) {
    _app_ctx.target_fps = 0;
    return *this;
  }

  BUILDER_FN(enableVsync()) {
    _app_ctx.is_vsync = true;
    return *this;
  }

  BUILDER_FN(enableWindowResizing()) {
    _app_ctx.is_resizeable = true;
    return *this;
  }

  BUILDER_FN(disableVsync()) {
    _app_ctx.is_vsync = false;
    return *this;
  }

  BUILDER_FN(disableWindowResizing()) {
    _app_ctx.is_resizeable = false;
    return *this;
  }

  [[nodiscard]] constexpr AppContext build() const noexcept {
    return _app_ctx;
  }

  #undef BUILDER_FN

};

} // namespace dull::misc
