#pragma once

#include "engine/core/node.hpp"
#include <vendor/zutils/zutils.hpp>

#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <type_traits>

namespace dull::core {
/// TODO: Need to move function bodies to .cpp

class Layer final {
private:
  std::string _name;
  std::vector<std::unique_ptr<Node>> _nodes;

  [[nodiscard]] auto _findIterator(std::string_view name) noexcept {
    return std::find_if(
      _nodes.begin(), _nodes.end(),
      [&name](const auto& node) { return node->getName() == name; }
    );
  }

  [[nodiscard]] auto _findIterator(std::string_view name) const noexcept {
    return std::find_if(
      _nodes.begin(), _nodes.end(),
      [&name](const auto& node) { return node->getName() == name; }
    );
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] auto _findIterator() noexcept {
    return std::find_if(
      _nodes.begin(), _nodes.end(),
      [](const auto& node) { return dynamic_cast<NodeT*>(node.get()) != nullptr; }
    );
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] auto _findIterator() const noexcept {
    return std::find_if(
      _nodes.begin(), _nodes.end(),
      [](const auto& node) { return dynamic_cast<NodeT*>(node.get()) != nullptr; }
    );
  }

public:
  static constexpr size_t DEFAULT_CAPACITY = 16;

  Layer() = delete;
  explicit Layer(std::string_view name, size_t initial_capacity = DEFAULT_CAPACITY)
  : _name{name} {
    _nodes.reserve(initial_capacity);
  }

  Layer(const Layer&)            = delete;
  Layer(Layer&&)                 = delete;
  Layer& operator=(const Layer&) = delete;
  Layer& operator=(Layer&&)      = delete;

  [[nodiscard]] std::string_view getName() const noexcept { return _name; }
  void setName(std::string_view name) noexcept { _name = name; }

  [[nodiscard]] constexpr size_t size() const noexcept { return _nodes.size(); }
  [[nodiscard]] constexpr bool empty() const noexcept { return _nodes.empty(); }

  void shrinkToFit() noexcept { _nodes.shrink_to_fit(); }

  template <typename NodeType = Node, typename... Args>
    requires std::is_base_of_v<Node, NodeType>
  NodeType* createNode(std::string_view name, Args &&...args) {
    auto node = std::make_unique<NodeType>(name, std::forward<Args>(args)...);
    auto *raw_ptr = node.get();
    _nodes.emplace_back(std::move(node));
    return raw_ptr;
  }

  void addNode(std::unique_ptr<Node> node) noexcept { _nodes.emplace_back(std::move(node)); }

  [[nodiscard]] Node* findNode(std::string_view name) noexcept {
    auto it = _findIterator(name);
    return it != _nodes.end() ? it->get() : nullptr;
  }

  [[nodiscard]] const Node* findNode(std::string_view name) const noexcept {
    auto it = _findIterator(name);
    return it != _nodes.end() ? it->get() : nullptr;
  }

  [[nodiscard]] Node* tryGetNode(std::string_view name) const noexcept {
    return const_cast<Node*>(std::as_const(*this).findNode(name));
  }

  [[nodiscard]] Node& getNode(std::string_view name) const {
    auto it = _findIterator(name);
    ZASSERT_NE(it, _nodes.end());
    return **it;
  }

  [[nodiscard]] bool hasNode(std::string_view name) const noexcept { return findNode(name) != nullptr; }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT* findNode() noexcept {
    auto it = _findIterator<NodeT>();
    return it != _nodes.end() ? static_cast<NodeT*>(it->get()) : nullptr;
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] const NodeT* findNode() const noexcept {
    auto it = _findIterator<NodeT>();
    return it != _nodes.end() ? static_cast<const NodeT*>(it->get()) : nullptr;
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT& getNode() const {
    auto* node = findNode<NodeT>();
    ZASSERT_NE(node, nullptr);
    return *node;
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] bool hasNode() const noexcept { return findNode<NodeT>() != nullptr; }

  [[nodiscard]] Node* getNodeByIndex(size_t index) noexcept {
    return index < _nodes.size() ? _nodes[index].get() : nullptr;
  }

  [[nodiscard]] const Node* getNodeByIndex(size_t index) const noexcept {
    return index < _nodes.size() ? _nodes[index].get() : nullptr;
  }

  void removeNode(std::string_view name) noexcept {
    std::erase_if(_nodes, [&name](const auto& node) { return node->getName() == name; });
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  void removeNode() noexcept {
    std::erase_if(_nodes, [](const auto& node) { return dynamic_cast<NodeT*>(node.get()) != nullptr; });
  }

  void removeAllNodes() noexcept { _nodes.clear(); }

  [[nodiscard]] std::unique_ptr<Node>
  extractNode(std::string_view name) noexcept {
    auto it = _findIterator(name);
    std::unique_ptr<Node> node {};

    if (it != _nodes.end()) {
      node = std::move(*it);
      _nodes.erase(it);
    }

    return node;
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] std::unique_ptr<NodeT> extractNode() noexcept {
    auto it = _findIterator<NodeT>();
    std::unique_ptr<Node> node {};

    if (it != _nodes.end()) {
      node = std::move(*it);
      _nodes.erase(it);
    }

    return node;
  }

  template <typename Func> void forEach(Func&& func) const {
    for (const auto& NODE : _nodes) std::invoke(func, *NODE);
  }

  template <typename NodeT, typename Func>
    requires std::is_base_of_v<Node, NodeT>
  void forEachOfType(Func&& func) const {
    for (const auto& NODE : _nodes)
      if (auto* casted = dynamic_cast<NodeT*>(NODE.get())) std::invoke(func, *casted);
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] std::vector<NodeT*> getAllNodesOfType() const {
    std::vector<NodeT*> result;

    for (const auto& NODE : _nodes)
      if (auto* casted = dynamic_cast<NodeT*>(NODE.get())) result.push_back(casted);

    result.shrink_to_fit();
    return result;
  }
};

} // namespace dull::core
