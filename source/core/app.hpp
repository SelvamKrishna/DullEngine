#pragma once

#include <string>

#include "../plugins/audio_system.hpp"
#include "../plugins/render_system.hpp"
#include "../plugins/time_system.hpp"
#include "scene.hpp"

/// A singleton class for managing the application lifecycle and main loop.
class App {
private:
  static constexpr float k_fixed_frame_rate = 60.0f;
  static constexpr float k_fixed_delta_time = 1.0f / k_fixed_frame_rate;

  Scene* _current_scene = nullptr;
  float _accumulator = 0.0f;
  bool _is_running = false;

  TimeSystem& _time_system = TimeSystem::instance();
  AudioSystem& _audio_system = AudioSystem::instance();
  RenderSystem* _render_system = nullptr;
  /// TODO: Implement Overridable Physics System

private:
  App() = default;
  ~App();

  App(const App&) = delete;
  App(App&&) = delete;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = delete;

  void _processNull();
  void _processFixed(float delta_time);
  void _process();

public:
  [[nodiscard]] static inline App& instance() noexcept {
    static App instance;
    return instance;
  }

  void init(int width, int height, std::string title);
  void run();
  inline void quit() noexcept { _is_running = false; }

  [[nodiscard]] bool isRunning() const noexcept { return _is_running; }

  void setCurrentScene(Scene* scene) noexcept { _current_scene = scene; }
  [[nodiscard]] inline Scene& currentScene() noexcept { return *_current_scene; }

  void setRenderSystem(RenderSystem* render_system) {
    _render_system = render_system ? render_system : &RenderSystem::instance();
  }

  [[nodiscard]] inline RenderSystem& renderSystem() noexcept { return *_render_system; }
};