#include "app.hpp"

#include <iostream>
#include <stdexcept>

#include "../../vendor/raylib.h"
#include "../plugins/time_system.hpp"

App::~App() {
  if (_root) {
    _root->Free();
    _root.reset();
  }
  CloseWindow();
}

void App::Init(const int width, const int height, std::string title) {
  InitWindow(width, height, title.c_str());
  SetExitKey(KEY_NULL);
  _isRunning = true;
}

void App::Run() {
  if (!_isRunning) throw std::runtime_error("App is not yet initialized.");
  if (!_root) throw std::runtime_error("App root is not yet set.");

  TimeSystem& timeSystem = TimeSystem::Instance();

  while (_isRunning) [[likely]] {
    try {
      if (WindowShouldClose()) [[unlikely]] {
        _isRunning = false;
        break;
      }

      const float kDeltaTime = GetFrameTime();
      timeSystem._deltaTime = kDeltaTime;
      timeSystem._UpdateInfo();

      if (timeSystem.IsPaused()) {
        BeginDrawing();
        EndDrawing();
        continue;
      }

      _accumulator += kDeltaTime;

      while (_accumulator >= kFixedDeltaTime) [[unlikely]] {
        _root->_FixedUpdate();
        _accumulator -= kFixedDeltaTime;
      }

      _root->_UpdateTree();

      // TODO: Proper Render System
      BeginDrawing();
      ClearBackground(BLACK);
      DrawFPS(10, 10);
      EndDrawing();
    } catch (std::exception& e) {
      _isRunning = false;
      std::cerr << "Exception: " << e.what() << std::endl;
    }
  }
}