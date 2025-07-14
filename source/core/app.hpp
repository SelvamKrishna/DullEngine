#pragma once

#include <string>

#include "../plugins/audio_system.hpp"
#include "../plugins/render_system.hpp"
#include "../plugins/time_system.hpp"
#include "scene.hpp"

/// A singleton class to manage the application.
class App {
private:
  /// TODO: Move to Time System
  static constexpr float k_fixed_frame_rate = 60.0f;
  static constexpr float k_fixed_delta_time = 1.0f / k_fixed_frame_rate;

  Scene* _current_scene = nullptr;
  float _accumulator = 0.0f;  /// Accumulator for fixed updates
  bool _is_running = false;

  TimeSystem& _time_system = TimeSystem::instance();
  AudioSystem& _audio_system = AudioSystem::instance();
  RenderSystem* _render_system = nullptr;
  /// TODO: Implement Overridable Physics System

private:
  App() = default;
  ~App();

  void _processNull();                   /// Process when the app is paused or null
  void _processFixed(float delta_time);  /// Process fixed updates
  void _process();                       /// Process regular updates

public:
  App(const App&) = delete;
  App(App&&) = delete;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = delete;

  [[nodiscard]] static inline App& instance() noexcept {
    static App instance;
    return instance;
  }

  void init(int window_width, int window_height, const std::string& title);
  void run();
  inline void quit() noexcept { _is_running = false; }

  void setCurrentScene(Scene* scene) noexcept { _current_scene = scene; }
  void setRenderSystem(RenderSystem* render_system) { _render_system = render_system; }

  [[nodiscard]] inline Scene& currentScene() noexcept { return *_current_scene; }
  [[nodiscard]] bool isRunning() const noexcept { return _is_running; }

  [[nodiscard]] inline TimeSystem& timeSystem() noexcept { return _time_system; }
  [[nodiscard]] inline AudioSystem& audioSystem() noexcept { return _audio_system; }
  [[nodiscard]] inline RenderSystem& renderSystem() noexcept { return *_render_system; }

  [[nodiscard]] inline float fixedFrameRate() const noexcept { return k_fixed_frame_rate; }
  [[nodiscard]] inline float fixedDeltaTime() const noexcept { return k_fixed_delta_time; }
};