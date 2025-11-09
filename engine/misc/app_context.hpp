#pragma once

#include "engine/util/vec2.hpp"

#include <string>

namespace dull::misc {

struct AppContext final {
  std::string title;
  util::Vec2i window_size {1280, 720};
  int target_fps {0}; // 0 disables frame limiting
  bool is_vsync {false}; // limits frame to monitor cap
  bool is_resizeable {false};
};

class AppContextBuilder final {
private:
  AppContext _app_ctx {};

public:
  explicit constexpr AppContextBuilder() = default;

  [[nodiscard]] constexpr AppContextBuilder& setTitle(std::string new_title) noexcept {
    _app_ctx.title = std::move(new_title);
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& setWindowSize(util::Vec2i new_size) noexcept {
    _app_ctx.window_size = new_size;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& setWindowWidth(float new_width) noexcept {
    _app_ctx.window_size.x = new_width;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& setWindowHeight(float new_height) noexcept {
    _app_ctx.window_size.y = new_height;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& setTargetFPS(int new_fps) noexcept {
    _app_ctx.target_fps = new_fps;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& maxTargetFPS() noexcept {
    _app_ctx.target_fps = 0;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& enableVsync() noexcept {
    _app_ctx.is_vsync = true;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& enableWindowResizing() noexcept {
    _app_ctx.is_resizeable = true;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& disableVsync() noexcept {
    _app_ctx.is_vsync = false;
    return *this;
  }

  [[nodiscard]] constexpr AppContextBuilder& disableWindowResizing() noexcept {
    _app_ctx.is_resizeable = false;
    return *this;
  }

  [[nodiscard]] constexpr AppContext build() const noexcept {
    return _app_ctx;
  }
};

} // namespace dull::misc
