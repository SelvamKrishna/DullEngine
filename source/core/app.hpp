#pragma once

#include <memory>
#include <string>

#include "node.hpp"

class App {
private:
  static constexpr float kFixedFrameRate = 60.0f;
  static constexpr float kFixedDeltaTime = 1.0f / kFixedFrameRate;

  std::unique_ptr<Node> _root;
  float _accumulator = 0.0f;
  bool _isRunning = false;

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
  [[nodiscard]] static inline App& Instance() noexcept {
    static App instance;
    return instance;
  }

  void Init(int width, int height, std::string title);
  void Run();
  inline void Quit() noexcept { _isRunning = false; }

  void SetRoot(Node* root) noexcept {
    _root.reset(root);
    if (_root) _root->_Init();
    _root->_state = Node::State::Active;
  }

  [[nodiscard]] inline Node* Root() noexcept { return _root.get(); }
  [[nodiscard]] inline const Node* Root() const noexcept { return _root.get(); }
};