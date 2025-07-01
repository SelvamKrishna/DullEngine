#include "node.hpp"

#include <algorithm>
#include <cassert>
#include <format>
#include <stdexcept>

Node::Node(const std::string &name) : _name(name) {}

void Node::_updateTree() {
  if (_state != State::Active) return;

  _update();

  for (const auto &child : _children) {
    if (!child) throw std::runtime_error(std::format("Null Child in Node: {}", _name));
    child->_updateTree();
  }
}

void Node::_fixedUpdateTree() {
  if (_state != State::Active) return;

  _fixedUpdate();

  for (const auto &child : _children) {
    if (!child) throw std::runtime_error(std::format("Null Child in Node: {}", _name));
    child->_fixedUpdateTree();
  }
}

void Node::free() noexcept {
  _parent = nullptr;
  _children.clear();
  _state = State::Uninitialized;
}

void Node::addChild(std::unique_ptr<Node> child) {
  if (!child) return;  // You can add a warning or log here if needed

  for (const auto &ptr : _children) {
    if (ptr && ptr->_name == child->_name) {
      throw std::runtime_error(
        std::format("Child: {} already exists in Node: {}", child->_name, _name));
    }
  }

  child->_parent = this;
  child->_init();
  child->_state = State::Active;

  _children.emplace_back(std::move(child));
}

void Node::removeChild(Node *child) {
  if (!child) return;  // You can add a warning or log here if needed

  for (const auto &ptr : _children) {
    if (ptr.get() == child) {
      ptr->_parent = nullptr;
      _children.erase(std::remove(_children.begin(), _children.end(), ptr), _children.end());
      return;
    }
  }

  throw std::runtime_error(std::format("Child: {} not found in Node: {}", child->_name, _name));
}

Node &Node::childByIndex(size_t index) {
  if (index >= _children.size())
    throw std::out_of_range(std::format("Child index {} out of bounds in Node: {}", index, _name));

  return *(_children[index]);
}

Node &Node::childByName(std::string_view name) {
  for (const auto &child : _children)
    if (child->_name == name) return *child;

  throw std::runtime_error(std::format("Child: {} not found in Node: {}", name, _name));
}
