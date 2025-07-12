#include "app.hpp"

#include <iostream>
#include <stdexcept>

#include "../../vendor/raylib.h"

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

void App::init(const int width, const int height, std::string title) {
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_NULL);
  _is_running = true;

  AudioSystem::instance()._init();
}

void App::run() {
  if (!_is_running) throw std::runtime_error("App is not yet initialized.");
  if (!_current_scene) throw std::runtime_error("App current scene is not yet set.");

  if (!_render_system) _render_system = &RenderSystem::instance();

  while (_is_running) [[likely]] {
    try {
      if (WindowShouldClose()) [[unlikely]] {
        _is_running = false;
        break;
      }

      _time_system._updateInfo(GetFrameTime());

      if (_time_system.isPaused()) _processNull();
      else _process();

    } catch (std::exception& e) {
      _is_running = false;
      std::cerr << "Runtime Exception: \n" << e.what() << std::endl;
    }
  }
}