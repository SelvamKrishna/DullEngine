#include "engine/config.hpp"
#include "engine/core/layer.hpp"

namespace dull::core {

[[nodiscard]] Layer::NodeIt Layer::_findIterator(std::string_view name) noexcept {
  return std::find_if(
    _nodes.begin(), _nodes.end(),
    [&name](const auto& node) { return node->getName() == name; }
  );
}

[[nodiscard]] Layer::NodeConstIt Layer::_findIterator(std::string_view name) const noexcept {
  return std::find_if(
    _nodes.begin(), _nodes.end(),
    [&name](const auto& node) { return node->getName() == name; }
  );
}

void Layer::addNode(std::unique_ptr<Node> node) noexcept {
  _nodes.emplace_back(std::move(node));

  ZLOGI_IF(config::SHOULD_LOG_SCENE_SYS)
    << "Add Node : Node (" << _nodes[_nodes.size() - 1]->getName() << ") -> Layer (" << _name << ")";
}

void Layer::removeNode(std::string_view name) noexcept {
  std::erase_if(_nodes, [&name](const auto& node) { return node->getName() == name; });

  ZLOGI_IF(config::SHOULD_LOG_SCENE_SYS)
    << "Remove Node : Node (" << name << ") -> Layer (" << _name << ")";
}

void Layer::removeAllNodes() noexcept {
  _nodes.clear();

  ZLOGI_IF(config::SHOULD_LOG_SCENE_SYS)
    << "Remove All Nodes : Layer (" << _name << ")";
}

[[nodiscard]] Node* Layer::findNode(this auto& self, std::string_view name) noexcept {
  auto it = self._findIterator(name);
  return it != self._nodes.end() ? it->get() : nullptr;
}

[[nodiscard]] Node& Layer::getNode(std::string_view name) const {
  auto it = _findIterator(name);
  ZASSERT_NE(it, _nodes.end());
  return **it;
}

[[nodiscard]] Node* Layer::tryGetNode(std::string_view name) const noexcept {
  return const_cast<Node*>(this->findNode(name));
}

[[nodiscard]] Node* Layer::getNodeByIndex(this auto& self, size_t index) noexcept {
  return index < self._nodes.size() ? self._nodes[index].get() : nullptr;
}

[[nodiscard]] std::unique_ptr<Node> Layer::extractNode(std::string_view name) noexcept {
  auto it = _findIterator(name);
  std::unique_ptr<Node> node {};

  if (it != _nodes.end()) {
    ZLOGI_IF(config::SHOULD_LOG_SCENE_SYS) << "Extract Nodes :";

    node = std::move(*it);
    _nodes.erase(it);
  } else ZLOGI_IF(config::SHOULD_LOG_SCENE_SYS) << "Extract Nodes (NOT FOUND):";

  ZLOGI_IF(config::SHOULD_LOG_SCENE_SYS)
    << "Node (" << name << ") -> Layer (" << _name << ")";

  return node;
}

} // namespace dull::core
