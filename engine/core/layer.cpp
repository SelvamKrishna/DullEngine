#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/core/layer.hpp"
#include "engine/core/node_handle.hpp"

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

void Layer::_disconnect(NodeIt node_it) noexcept { node_it->uptr->_layer_name = ""; }

void Layer::addNode(std::string name, std::unique_ptr<Node> node, bool is_active) noexcept
{
    ZASSERT(
        std::find_if(
            _nodes.begin(), _nodes.end(),
            [&name](const CtxNodePair& node) { return node.name == name; }
        ) == _nodes.end(),
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

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();
    _IF_LOG ZINFO("All Nodes removed from Layer '{}'", _name);
}

[[nodiscard]]
NodeHandle Layer::getNodeHandle(std::string_view name) noexcept
{
    std::vector<CtxNodePair>::iterator it = std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const CtxNodePair& node)
        { return node.name == name; }
    );

    ZASSERT(
        it != _nodes.end(),
        "Unable to find Node '{}' in Layer '{}'",
        name, _name
    );

    return NodeHandle { *this, it };
}

[[nodiscard]]
NodeHandle Layer::getNodeHandle(size_t index) noexcept
{
    ZASSERT(
        index < _nodes.size(),
        "Node index {} out of range in Layer '{}'",
        index, _name
    );

    std::vector<CtxNodePair>::iterator it = _nodes.begin() + index;

    return NodeHandle { *this, it };
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
