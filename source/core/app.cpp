#include "app.hpp"

#include <iostream>
#include <stdexcept>

#include "../../vendor/raylib.h"
#include "../plugins/audio_system.hpp"
#include "../plugins/time_system.hpp"

App::~App() {
  if (_root) {
    _root->free();
    _root.reset();
  }

  CloseWindow();
}

void App::init(const int width, const int height, std::string title) {
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_NULL);
  _is_running = true;

  AudioSystem::instance()._init();
}

void App::run() {
  if (!_is_running) throw std::runtime_error("App is not yet initialized.");
  if (!_root) throw std::runtime_error("App root is not yet set.");

  TimeSystem& time_system = TimeSystem::instance();
  AudioSystem& audio_system = AudioSystem::instance();

  while (_is_running) [[likely]] {
    try {
      if (WindowShouldClose()) [[unlikely]] {
        _is_running = false;
        break;
      }

      const float k_delta_time = GetFrameTime();
      time_system._deltaTime = k_delta_time;
      time_system._updateInfo();

      if (time_system.isPaused()) {
        BeginDrawing();
        EndDrawing();
        continue;
      }

      _accumulator += k_delta_time;

      while (_accumulator >= k_fixed_delta_time) [[unlikely]] {
        _root->_fixedUpdate();
        _accumulator -= k_fixed_delta_time;
      }

      _root->_updateTree();

      // TODO: Proper Render System
      BeginDrawing();
      ClearBackground(BLACK);
      DrawFPS(10, 10);
      EndDrawing();

      audio_system._update();
    } catch (std::exception& e) {
      _is_running = false;
      std::cerr << "Exception: " << e.what() << std::endl;
    }
  }
}