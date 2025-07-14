#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>

#include "../utils/debug.hpp"
#include "node.hpp"

/// A class to represent a group of nodes that are processed together.
class Scene {
  friend class App;

private:
  static constexpr size_t k_default_node_buffer_size = 16;
  std::vector<std::unique_ptr<Node>> _nodes;

private:
  void _update();
  void _fixedUpdate();

public:
  explicit Scene(size_t node_buffer_size = k_default_node_buffer_size);
  ~Scene();

  void addNode(Node* node);
  void removeNode(Node* node);
  void clear();

  [[nodiscard]] inline size_t nodeCount() const noexcept { return _nodes.size(); }
  [[nodiscard]] Node* getNodeByIndex(size_t index);
  [[nodiscard]] Node* getNodeByName(const std::string& name);

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT* getNode() {
    for (auto& node : _nodes) {
      if (NodeT* casted_node = dynamic_cast<NodeT*>(node.get())) return casted_node;
    }

    DULL_WARN("dynamic_cast failed; getNode");
    return nullptr;
  }
};