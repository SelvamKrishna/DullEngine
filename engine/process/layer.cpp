#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/process/layer.hpp"
#include "engine/misc/node_handle.hpp"

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

Layer::Layer(std::string name, size_t reserve)
: misc::Identified<LayerTag> {std::move(name)}, _nodes {reserve}
{}

void Layer::iStart()
{
    forAllNodes([](Node& node) { node.iStart(); });
}

void Layer::iProcess()
{
    forAllNodes([](Node& node) { if (node.is_process) node.iProcess(); });
}

void Layer::iFixedProcess()
{
    forAllNodes([](Node& node) { if (node.is_fixed_process) node.iFixedProcess(); });
}

void Layer::_disconnect(Node::ID id) noexcept { _nodes.remove(id); }

void Layer::addNode(std::unique_ptr<Node> node, bool is_active) noexcept
{
    Node::ID node_id = node->getID();

    if (_nodes.size() == _nodes.capacity()) [[unlikely]]
    {
        ZPERFORMANCE(
            "Layer '{}' size exceeding capacity of '{}'",
            getName(), _nodes.size()
        );
    }

    _IF_LOG ZINFO("Node '{}' added to Layer '{}'", node->getName(), getName());
    ZVERIFY(
        _nodes.add(std::move(node)),
        "Failed to add Node #{} into Layer '{}'", node_id, getName()
    );

    Node& node_ref = getNodeHandle(node_id).getNode();

    if (!is_active) return; // Layer currently not processing

    if (DULL_HANDLE.isStarting())
        node_ref._is_active = true;
        // Soft active `Node::_start()` will be called in Layer::_active()
    else
        node_ref.setActive(true);
        // Hard active `Node::_start()` will be called now
}

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();
    _IF_LOG ZINFO("All Nodes removed from Layer '{}'", getName());
}

[[nodiscard]]
misc::LayerNodeHandle Layer::getNodeHandle(Node::ID node_id) noexcept
{
    return misc::LayerNodeHandle { *this, node_id };
}

void Layer::forAllNodes(const std::function<void(Node&)>& function) noexcept
{
    for (auto& node : _nodes) function(*node.get());
}

#undef _IF_LOG

} // namespace dull::process
