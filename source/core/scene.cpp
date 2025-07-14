#include "scene.hpp"

Scene::Scene(size_t node_buffer_size) {
  if (node_buffer_size > 0) _nodes.reserve(node_buffer_size);
}

Scene::~Scene() {
  clear();
}

void Scene::_update() {
  for (auto& node : _nodes) {
    if (node && node->_is_active) node->_update();
  }
}

void Scene::_fixedUpdate() {
  for (auto& node : _nodes) {
    if (node && node->_is_active) node->_fixedUpdate();
  }
}

void Scene::addNode(Node* node) {
  if (!node) throw std::runtime_error(TRACE_MSG("node = nullptr; addNode"));

  node->setActive(true);
  _nodes.emplace_back(node);
}

void Scene::removeNode(Node* node) {
  if (!node) throw std::runtime_error(TRACE_MSG("node = nullptr; removeNode"));

  for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
    if (it->get() == node) {
      _nodes.erase(it);
      return;
    }
  }

  DULL_WARN("Node not found; removeNode");
}

void Scene::clear() {
  _nodes.clear();
}

[[nodiscard]] Node* Scene::getNodeByIndex(size_t index) {
  if (index < _nodes.size()) return _nodes[index].get();

  DULL_WARN("Index out of range; getNodeByIndex");
  return nullptr;
}

[[nodiscard]] Node* Scene::getNodeByName(const std::string& name) {
  /// FIXME: Name collision not dealt with.

  for (auto& node : _nodes) {
    if (node && node->_name == name) return node.get();
  }

  DULL_WARN("Node not found; getNodeByName");
  return nullptr;
}