#pragma once

#include "engine/core/node.hpp"

#include <vendor/zutils/zutils.hpp>

#include <string>
#include <vector>
#include <memory>

namespace dull::core {

class Layer final {
private:
  std::string _name;
  std::vector<std::unique_ptr<Node>> _node_vec;

  [[nodiscard]] auto _findNode(std::string_view name) const {
    return std::find_if(
      _node_vec.begin(), _node_vec.end(),
      [&name](const std::unique_ptr<Node>& node) {
        return node->getName() == name;
      }
    );
  }

public:
  static constexpr size_t DEFAULT_NODE_VEC_SIZE = 16;

  Layer() = delete;
  explicit Layer(std::string_view name, size_t node_vec_size = DEFAULT_NODE_VEC_SIZE) : _name{name} {
    _node_vec.reserve(node_vec_size);
  }

  Layer(const Layer &)            = delete;
  Layer(Layer &&)                 = delete;
  Layer &operator=(const Layer &) = delete;
  Layer &operator=(Layer &&)      = delete;

  void addNode(std::unique_ptr<Node> node) noexcept {
    _node_vec.emplace_back(std::move(node));
  }

  void removeNode(std::string_view node_name) noexcept {
    std::erase_if(_node_vec, [&node_name](const std::unique_ptr<Node>& node) {
      return node->getName() == node_name;
    });
  }

  [[nodiscard]] bool hasNode(std::string_view node_name) noexcept {
    return _findNode(node_name) != _node_vec.end();
  }

  [[nodiscard]] Node* tryGetNode(std::string_view node_name) const noexcept {
    auto it = _findNode(node_name);
    return it != _node_vec.end() ? it->get() : nullptr;
  }

  [[nodiscard]] Node& getNode(std::string_view node_name) const noexcept {
    auto it = _findNode(node_name);
    ZASSERT_NE(it, _node_vec.end());
    return *it->get();
  }

  [[nodiscard]] constexpr std::string& getName() noexcept { return _name; }

};

class LayerBuffer final {
private:


public:

};

} // namespace dull::core
