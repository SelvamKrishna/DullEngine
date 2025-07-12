#pragma once

#include "../../vendor/raylib.h"

/// UNTESTED:
/// Class for managing rendering logic.
/// A global singleton system which handles all rendering operations.
/// Can be extended for custom rendering logic.
class RenderSystem {
private:
  friend class App;

private:
  RenderSystem() = default;
  ~RenderSystem() = default;

  RenderSystem(const RenderSystem &) = delete;
  RenderSystem(RenderSystem &&) = delete;
  RenderSystem &operator=(const RenderSystem &) = delete;
  RenderSystem &operator=(RenderSystem &&) = delete;

  inline void _drawNull() {
    BeginDrawing();
    EndDrawing();
  }

private:
  virtual void _update();

public:
  static RenderSystem &instance() {
    static RenderSystem instance;
    return instance;
  }
};