#pragma once

#include "engine/core/app.hpp"
#include "engine/misc/app_config.hpp"

#include <vendor/warp_mini.hpp>

namespace dull::misc {

class AppBuilder {
private:
  misc::AppConfig _app_config{};

public:
  explicit constexpr AppBuilder() = default;

  [[nodiscard]] constexpr AppBuilder& setTitle(std::string new_title) noexcept {
    _app_config.title = std::move(new_title);
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& setWindowSize(util::Vec2i new_size) noexcept {
    _app_config.window_size = new_size;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& setWindowWidth(float new_width) noexcept {
    _app_config.window_size.x = new_width;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& setWindowHeight(float new_height) noexcept {
    _app_config.window_size.y = new_height;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& setTargetFPS(int new_fps) noexcept {
    _app_config.target_fps = new_fps;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& maxTargetFPS() noexcept {
    _app_config.target_fps = 0;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& enableVsync() noexcept {
    _app_config.is_vsync = true;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& enableWindowResizing() noexcept {
    _app_config.is_resizeable = true;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& disableVsync() noexcept {
    _app_config.is_vsync = false;
    return *this;
  }

  [[nodiscard]] constexpr AppBuilder& disableWindowResizing() noexcept {
    _app_config.is_resizeable = false;
    return *this;
  }

  [[nodiscard]] core::App& build() const noexcept {
    core::App app {_app_config};
    return core::App::instance();
  }

  void buildAndRun() const noexcept {
    core::App{_app_config}.run();
  }
};

} // namespace dull::misc
