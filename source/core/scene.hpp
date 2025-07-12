#pragma once

#include <cstddef>
#include <memory>
#include <type_traits>
#include <vector>

#include "node.hpp"

class Scene {
private:
  friend class App;

private:
  std::vector<std::unique_ptr<Node>> _nodes;

public:
  explicit Scene(size_t node_buffer_size = 16);
  ~Scene();

private:
  void _update();
  void _fixedUpdate();

public:
  void addNode(Node* node);
  void removeNode(Node* node);

  [[nodiscard]] Node* getNodeByIndex(size_t index) {
    if (index < _nodes.size()) return _nodes[index].get();
    return nullptr;
  }

  [[nodiscard]] Node* getNodeByName(const std::string& name) {
    for (auto& node : _nodes) {
      if (node && node->_name == name) return node.get();
    }
    return nullptr;
  }

  template <typename NodeT>
    requires std::is_base_of_v<Node, NodeT>
  [[nodiscard]] NodeT* getNodeByType() {
    for (auto& node : _nodes) {
      if (NodeT* casted_node = dynamic_cast<NodeT*>(node.get())) return casted_node;
    }
    return nullptr;
  }

  void clear();
};