#pragma once

#include "../../vendor/raylib.h"

/// Class for managing rendering logic.
/// A global singleton system which handles all rendering operations.
/// Can be extended for custom rendering logic.
class RenderSystem {
private:
  friend class App;

private:
  RenderSystem(const RenderSystem &) = delete;
  RenderSystem(RenderSystem &&) = delete;
  RenderSystem &operator=(const RenderSystem &) = delete;
  RenderSystem &operator=(RenderSystem &&) = delete;

private:
  inline void _drawNull() {
    BeginDrawing();
    EndDrawing();
  }

  // Called once every frame.
  virtual void _update();

protected:
  RenderSystem() = default;

public:
  virtual ~RenderSystem() = default;

  static RenderSystem &instance() {
    static RenderSystem instance;
    return instance;
  }
};