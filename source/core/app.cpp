#include "app.hpp"

#include "../../vendor/raylib.h"
#include "../utils/debug.hpp"

App::~App() {
  CloseWindow();
}

void App::_processNull() {
  _render_system->_drawNull();
}

void App::_processFixed(float delta_time) {
  _accumulator += delta_time;

  while (_accumulator >= k_fixed_delta_time) [[unlikely]] {
    _current_scene->_fixedUpdate();
    _accumulator -= k_fixed_delta_time;
  }
}

void App::_process() {
  _processFixed(_time_system.deltaTime());

  _current_scene->_update();
  _render_system->_update();
  _audio_system._update();
}

void App::init(const int window_width, const int window_height, const std::string& title) {
  InitWindow(window_width, window_height, title.c_str());
  SetExitKey(KEY_NULL);
  _is_running = true;

  AudioSystem::instance()._init();
}

void App::run() {
  if (!_is_running) DULL_WARN("_is_running = false; run");
  if (!_current_scene) DULL_WARN("_current_scene = nullptr; run");

  if (!_render_system) _render_system = &RenderSystem::instance();

  while (_is_running) [[likely]] {
    try {
      if (WindowShouldClose()) [[unlikely]] {
        _is_running = false;
        break;
      }

      _time_system._updateInfo(GetFrameTime());
      _time_system.isPaused() ? _processNull() : _process();

    } catch (std::exception& runtime_err) {
      _is_running = false;
      DULL_WARN("%s", runtime_err.what());
    }
  }
}