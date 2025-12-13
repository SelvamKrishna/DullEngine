#include "engine/config.hpp"
#include "engine/core/layer.hpp"

#include <vendor/zutils/log.hpp>
#include <vendor/zutils/test.hpp>
#include <vendor/zutils/tools.hpp>

namespace dull::core {

[[nodiscard]]
Layer::NodeIt Layer::_findIterator(std::string_view name) noexcept
{
    return std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const auto& node) { return node.first == name; }
    );
}

[[nodiscard]]
Layer::NodeConstIt Layer::_findIterator(std::string_view name) const noexcept
{
    return std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const auto& node) { return node.first == name; }
    );
}

void Layer::addNode(std::string name, std::unique_ptr<Node> node) noexcept
{
    ZASSERT_S(
        _findIterator(name) == _nodes.end(),
        "Node with name '" + name + "' already exists in Layer (" + _name + ")"
    );

    _nodes.emplace_back(std::make_pair(std::move(name), std::move(node)));
    _nodes.back().second->_start();

    ZINFO_IF(
        config::SHOULD_LOG_SCENE_SYS,
        "Add Node : '{}' -> Layer ('{}')",
        _nodes[_nodes.size() - 1].first, _name
    );
}

void Layer::removeNode(std::string_view name) noexcept
{
    std::erase_if(_nodes, [&name](const auto& node) { return node.first == name; });

    ZINFO_IF(
        config::SHOULD_LOG_SCENE_SYS,
        "Remove Node : Node ('{}') -> Layer ('{}')",
        name, _name
    );
}

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();

    ZINFO_IF(
        config::SHOULD_LOG_SCENE_SYS,
        "Remove All Nodes : Layer ('{}')",
        _name
    );
}

[[nodiscard]]
Node* Layer::findNode(this auto& self, std::string_view name) noexcept
{
    auto it = self._findIterator(name);
    return it != self._nodes.end() ? it->second.get() : nullptr;
}

[[nodiscard]]
Node& Layer::getNode(std::string_view name) const
{
    auto it = _findIterator(name);
    ZASSERT_NE(it, _nodes.end());
    return *it->second;
}

[[nodiscard]]
Node* Layer::tryGetNode(std::string_view name) const noexcept
{
    return const_cast<Node*>(this->findNode(name));
}

[[nodiscard]]
Node* Layer::getNodeByIndex(this auto& self, size_t index) noexcept
{
    return index < self._nodes.size() ? self._nodes[index].second.get() : nullptr;
}

[[nodiscard]]
std::unique_ptr<Node> Layer::extractNode(std::string_view name) noexcept
{
    auto it = _findIterator(name);
    std::unique_ptr<Node> node {};

    if (it != _nodes.end())
    {
        ZINFO_IF(
            config::SHOULD_LOG_SCENE_SYS,
            "Extract Nodes :"
        );

        node = std::move(it->second);
        _nodes.erase(it);
    }
    else
    {
        ZINFO_IF(
            config::SHOULD_LOG_SCENE_SYS,
            "Extract Nodes (NOT FOUND):"
        );
    }

    ZINFO_IF(
        config::SHOULD_LOG_SCENE_SYS,
        "Node ('{}') -> Layer ('{}')",
        name, _name
    );
    return node;
}

void Layer::logStats() const noexcept
{
    ZON_RELEASE return;

    ZINFO_IF(config::SHOULD_LOG_SCENE_SYS, "Status -> Layer ({})", (void*)this);
    ZVAR(_name);
    ZVAR(_nodes.size());

    for (const auto& NODE : _nodes) ZVAR(NODE.first);
}

} // namespace dull::core
