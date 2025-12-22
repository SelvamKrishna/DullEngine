#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/process/layer.hpp"
#include "engine/process/node_handle.hpp"

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void Layer::iStart() { forAllNodes([](Node& node) { node.iStart(); }); }

void Layer::iProcess()
{
    forAllNodes(
        [](Node& node) { if (node.is_process) node.iProcess(); }
    );
}

void Layer::iFixedProcess()
{
    forAllNodes(
        [](Node& node) { if (node.is_fixed_process) node.iFixedProcess(); }
    );
}

void Layer::_disconnect(std::vector<NodeCtx>::iterator node_it) noexcept { _nodes.erase(node_it); }

void Layer::addNode(std::string name, std::unique_ptr<Node> node, bool is_active) noexcept
{
    ZASSERT(
        std::find_if(
            _nodes.begin(), _nodes.end(),
            [&name](const NodeCtx& node) { return node.name == name; }
        ) == _nodes.end(),
        "Node '{}' already exists in Layer '{}'", name, _name
    );

    _IF_LOG ZINFO("Node '{}' added to Layer '{}'", name, _name);
    _nodes.emplace_back(NodeCtx { .name = std::move(name), .uptr = std::move(node) });

    if (!is_active) return;

    if (DULL_HANDLE.isStarting())
        _nodes.back().uptr->_is_active = true;
        // Soft active `Node::_start()` will be called in Layer::_active()
    else
        _nodes.back().uptr->setActive(true);
        // Hard active `Node::_start()` will be called now
}

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();
    _IF_LOG ZINFO("All Nodes removed from Layer '{}'", _name);
}

[[nodiscard]]
NodeHandle Layer::getNodeHandle(std::string_view name) noexcept
{
    std::vector<NodeCtx>::iterator it = std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const NodeCtx& node)
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

    std::vector<NodeCtx>::iterator it = _nodes.begin() + index;

    return NodeHandle { *this, it };
}

void Layer::forAllNodes(const std::function<void(Node&)>& function) noexcept
{
    for (const auto& [NAME, U_PTR] : _nodes) function(*U_PTR.get());
}

void Layer::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging Layer '{}'", _name);
    for (const NodeCtx& NODE : _nodes)
    {
        ZDBG(
            "{}Node '{}'{}{}",
            zlog::config::TAB_TAG,
            NODE.name,
            zlog::config::TAG_TAG,
            NODE.uptr->isActive()
        );
    }
}

#undef _IF_LOG

} // namespace dull::process
