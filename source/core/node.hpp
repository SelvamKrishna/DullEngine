#pragma once

#include <cstdint>
#include <string>

/// A base class for all nodes in the application.
/// Nodes can be used to create a hierarchy of objects, such as game entities or UI components
class Node {
private:
  friend class App;
  friend class Scene;

public:
  enum class State : uint8_t {
    Uninitialized,
    Active,
    Disabled,
  };

protected:
  std::string _name;
  State _state = State::Uninitialized;

private:
  virtual void _init() {}
  virtual void _update() {}
  virtual void _fixedUpdate() {}

public:
  explicit Node(const std::string &name);
  virtual ~Node() = default;

  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) noexcept = default;
};
