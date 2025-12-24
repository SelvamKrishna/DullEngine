#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/process/layer.hpp"
#include "engine/misc/node_handle.hpp"

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void Layer::iStart() { forAllNodes([](Node& node) { node.iStart(); }); }

void Layer::iProcess()
{
    forAllNodes([](Node& node) { if (node.is_process) node.iProcess(); });
}

void Layer::iFixedProcess()
{
    forAllNodes([](Node& node) { if (node.is_fixed_process) node.iFixedProcess(); });
}

void Layer::_disconnect(NodeIt node_it) noexcept { _nodes.erase(node_it); }

void Layer::addNode(std::unique_ptr<Node> node, bool is_active) noexcept
{
    std::string_view node_name;

    ZASSERT(
        std::find_if(
            _nodes.begin(), _nodes.end(),
            [&node_name](const std::unique_ptr<Node>& node)
            { return node->getName() == node_name; }
        ) == _nodes.end(),
        "Node '{}' already exists in Layer '{}'", node_name, _name
    );

    _IF_LOG ZINFO("Node '{}' added to Layer '{}'", node_name, _name);
    _nodes.emplace_back(std::move(node));

    if (!is_active) return; // Layer currently not processing

    ZON_DEBUG {
        if (_nodes.size() == _nodes.capacity()) [[unlikely]]
            ZPERFORMANCE("Layer '{}' size exceeding capacity of '{}'", _name, _nodes.size());
    }

    if (DULL_HANDLE.isStarting())
        _nodes.back()->_is_active = true;
        // Soft active `Node::_start()` will be called in Layer::_active()
    else
        _nodes.back()->setActive(true);
        // Hard active `Node::_start()` will be called now
}

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();
    _IF_LOG ZINFO("All Nodes removed from Layer '{}'", _name);
}

[[nodiscard]]
misc::LayerNodeHandle Layer::getNodeHandle(std::string_view name) noexcept
{
    NodeIt it = std::find_if(
        _nodes.begin(), _nodes.end(),
        [&name](const std::unique_ptr<Node>& node)
        { return node->getName() == name; }
    );

    ZASSERT(
        it != _nodes.end(),
        "Unable to find Node '{}' in Layer '{}'",
        name, _name
    );

    return misc::LayerNodeHandle { *this, it };
}

[[nodiscard]]
misc::LayerNodeHandle Layer::getNodeHandle(size_t index) noexcept
{
    ZASSERT(
        index < _nodes.size(),
        "Node index {} out of range in Layer '{}'",
        index, _name
    );

    return misc::LayerNodeHandle { *this, _nodes.begin() + index };
}

void Layer::forAllNodes(const std::function<void(Node&)>& function) noexcept
{
    for (auto& node : _nodes) function(*node.get());
}

void Layer::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging Layer '{}'", _name);
    for (const auto& NODE : _nodes)
    {
        ZDBG(
            "{}Node '{}'{}{}",
            zlog::config::TAB_TAG,
            NODE->getName(),
            zlog::config::TAG_TAG,
            NODE->isActive()
        );
    }
}

#undef _IF_LOG

} // namespace dull::process
