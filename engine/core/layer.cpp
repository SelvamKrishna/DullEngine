#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/core/layer.hpp"

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_LAYER_SYS)

#define _FOR_ALL_ACTIVE_NODES \
    for (auto& node : _nodes) if (node.uptr->isActive())

void Layer::_activate()
{
    _FOR_ALL_ACTIVE_NODES
        node.uptr->_start();
}

void Layer::_process()
{
    _FOR_ALL_ACTIVE_NODES
        if (node.uptr->is_process) node.uptr->_update();
}

void Layer::_fixedProcess()
{
    _FOR_ALL_ACTIVE_NODES
        if (node.uptr->is_fixed_process) node.uptr->_fixedUpdate();
}

#undef _FOR_ALL_ACTIVE_NODES

[[nodiscard]]
Layer::NodeIt Layer::_findIterator(std::string_view name) noexcept
{
    return std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const CtxNodePair& node) { return node.name == name; }
    );
}

[[nodiscard]]
Layer::NodeConstIt Layer::_findIterator(std::string_view name) const noexcept
{
    return std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const CtxNodePair& node) { return node.name == name; }
    );
}

void Layer::addNode(std::string name, std::unique_ptr<Node> node, bool is_active) noexcept
{
    ZASSERT(
        _findIterator(name) == _nodes.end(),
        "Node '{}' already exists in Layer '{}'", name, _name
    );

    _IF_LOG ZINFO("Node '{}' added to Layer '{}'", name, _name);
    node->_layer_name = _name;
    _nodes.emplace_back(CtxNodePair { .name = std::move(name), .uptr = std::move(node) });

    if (!is_active) return;

    switch (DULL_HANDLE.getProgramState()) {
        case ProgramState::Initial:
        {
            // Soft active `Node::_start()` will be called later
            _nodes.back().uptr->_is_active = true; break;
        }
        case ProgramState::Process:
        {
            // Hard active `Node::_start()` will be called now
            _nodes.back().uptr->setActive(true); break;
        }
        case ProgramState::Conclude: break;
    }
}

void Layer::removeNode(std::string_view name) noexcept
{
    std::erase_if(_nodes, [&name](const CtxNodePair& node) { return node.name == name; });
    _IF_LOG ZINFO("Node '{}' removed from Layer '{}'", name, _name);
}

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();
    _IF_LOG ZINFO("All Nodes removed from Layer '{}'", _name);
}

[[nodiscard]]
Node* Layer::findNode(std::string_view name) noexcept
{
    auto it = _findIterator(name);
    return it != _nodes.end() ? it->uptr.get() : nullptr;
}

const Node* Layer::findNode(std::string_view name) const noexcept
{
    auto it = _findIterator(name);
    return it != _nodes.end() ? it->uptr.get() : nullptr;
}

[[nodiscard]]
const Node& Layer::getNode(std::string_view name) const
{
    auto* NODE = findNode(name);
    ZASSERT(NODE != nullptr);
    return *NODE;
}

[[nodiscard]]
Node& Layer::getNode(std::string_view name)
{
    auto* node = findNode(name);
    ZASSERT(node != nullptr);
    return *node;
}

[[nodiscard]]
Node* Layer::tryGetNode(std::string_view name) const noexcept
{
    return const_cast<Node*>(this->findNode(name));
}

[[nodiscard]]
Node* Layer::getNodeByIndex(this auto& self, size_t index) noexcept
{
    return index < self._nodes.size() ? self._nodes[index].uptr.get() : nullptr;
}

[[nodiscard]]
std::unique_ptr<Node> Layer::extractNode(std::string_view name) noexcept
{
    auto it = _findIterator(name);

    if (it == _nodes.end())
    {
        _IF_LOG ZINFO("Can't extract Node '{}' from Layer '{}'", name, _name);
        return std::unique_ptr<Node>{nullptr};
    }

    _IF_LOG ZINFO("Node '{}' extracted from Layer '{}'", name, _name);

    std::unique_ptr<Node> node = {std::move(it->uptr)};
    node->_layer_name = "";
    _nodes.erase(it);

    return node;
}

void Layer::logStats() const noexcept
{
    ZON_RELEASE return;
    ZINFO_IF(config::SHOULD_LOG_SCENE_SYS, "Status -> Layer ({})", (void*)this);
    ZVAR(_name);
    ZVAR(_nodes.size());

    for (const CtxNodePair& NODE : _nodes) ZVAR(NODE.name);
}

#undef _IF_LOG

} // namespace dull::core

