#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

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
  virtual void _Init() {}
  virtual void _Update() {}
  virtual void _FixedUpdate() {}

  void _UpdateTree();
  void _FixedUpdateTree();

public:
  explicit Node(const std::string &name);
  virtual ~Node() = default;

  Node(const Node &) = delete;
  Node(Node &&) noexcept = default;
  Node &operator=(const Node &) = delete;
  Node &operator=(Node &&) noexcept = default;

  void Free() noexcept;

  void AddChild(std::unique_ptr<Node> child);
  void RemoveChild(Node *child);

  [[nodiscard]] Node &ChildByIndex(size_t index);
  [[nodiscard]] Node &ChildByName(std::string_view name);

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT *ChildByType() {
    for (auto &child : _children)
      if (NodeT *casted = dynamic_cast<NodeT *>(child.get()); casted) return casted;

    return nullptr;
  }

  [[nodiscard]] inline size_t ChildCount() const noexcept { return _children.size(); }
  [[nodiscard]] inline const Node *Parent() const noexcept { return _parent; }
  [[nodiscard]] inline std::string_view Name() const noexcept { return _name; }
  [[nodiscard]] inline const ChildrenArray *Children() const noexcept { return &_children; }
};
