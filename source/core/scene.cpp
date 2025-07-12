#include "scene.hpp"

#include <stdexcept>

[[noreturn]] static void nullNodeError() {
  throw std::runtime_error("Node cannot be null");
}

Scene::Scene(size_t node_buffer_size) {
  if (node_buffer_size > 0) _nodes.reserve(node_buffer_size);
}

Scene::~Scene() {
  clear();
}

void Scene::_update() {
  for (auto& node : _nodes) {
    if (node && node->_state == Node::State::Active) node->_update();
  }
}

void Scene::_fixedUpdate() {
  for (auto& node : _nodes) {
    if (node && node->_state == Node::State::Active) node->_fixedUpdate();
  }
}

void Scene::addNode(Node* node) {
  if (!node) return nullNodeError();
  _nodes.emplace_back(node);
}

void Scene::removeNode(Node* node) {
  if (!node) return nullNodeError();

  for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
    if (it->get() == node) {
      _nodes.erase(it);
      return;
    }
  }
}

void Scene::clear() {
  _nodes.clear();
}