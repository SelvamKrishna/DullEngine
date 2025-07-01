#pragma once

#include <memory>
#include <string>

#include "node.hpp"

class App {
private:
  static constexpr float k_fixed_frame_rate = 60.0f;
  static constexpr float k_fixed_delta_time = 1.0f / k_fixed_frame_rate;

  std::unique_ptr<Node> _root;
  float _accumulator = 0.0f;
  bool _is_running = false;

  // TODO: Implement Render System
  // TODO: Implement Physics System
  // TODO: Implement Audio System

private:
  App() = default;
  ~App();

  App(const App&) = delete;
  App(App&&) = delete;
  App& operator=(const App&) = delete;
  App& operator=(App&&) = delete;

public:
  [[nodiscard]] static inline App& instance() noexcept {
    static App instance;
    return instance;
  }

  void init(int width, int height, std::string title);
  void run();
  inline void quit() noexcept { _is_running = false; }

  void setRoot(Node* root) noexcept {
    _root.reset(root);
    if (_root) _root->_init();
    _root->_state = Node::State::Active;
  }

  [[nodiscard]] inline Node* root() noexcept { return _root.get(); }
  [[nodiscard]] inline const Node* root() const noexcept { return _root.get(); }
};