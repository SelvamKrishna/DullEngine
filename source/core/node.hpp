#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

/// A base class for all nodes in the application.
/// Nodes can be used to create a hierarchy of objects, such as game entities or UI components
class Node {
private:
  friend class App;

public:
  enum class State : uint8_t {
    Uninitialized,
    Active,
    Disabled,
  };

protected:
  using ChildrenArray = std::vector<std::unique_ptr<Node>>;

  std::string _name;
  Node *_parent = nullptr;
  ChildrenArray _children;
  State _state = State::Uninitialized;

private:
  virtual void _init() {}
  virtual void _update() {}
  virtual void _fixedUpdate() {}

  void _updateTree();
  void _fixedUpdateTree();

public:
  explicit Node(const std::string &name);
  virtual ~Node() = default;

  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) noexcept = default;

  void free() noexcept;

  void addChild(std::unique_ptr<Node> child);
  void removeChild(Node *child);

  [[nodiscard]] Node &childByIndex(size_t index);
  [[nodiscard]] Node &childByName(std::string_view name);

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT *childByType() {
    for (auto &child : _children)
      if (NodeT *casted = dynamic_cast<NodeT *>(child.get()); casted) return casted;

    return nullptr;
  }

  [[nodiscard]] inline size_t childCount() const noexcept { return _children.size(); }
  [[nodiscard]] inline const Node *parent() const noexcept { return _parent; }
  [[nodiscard]] inline std::string_view name() const noexcept { return _name; }
  [[nodiscard]] inline const ChildrenArray *children() const noexcept { return &_children; }
};
