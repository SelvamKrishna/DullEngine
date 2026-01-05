#include "engine/config.hpp"
#include "engine/process/layer.hpp"
#include "engine/misc/node_handle.hpp"

namespace dull::process {

Layer::Layer(std::string name, size_t reserve)
: misc::Identified<LayerTag> {std::move(name)}, _nodes {reserve}
{}

#define _FOR_ALL_NODES(NODE_VAR, NODE_OPR) do {    \
    forAllNodes([](Node& NODE_VAR) { NODE_OPR; }); \
} while (0);

void Layer::iStart()        { _FOR_ALL_NODES(node, node._startNode()); }
void Layer::iProcess()      { _FOR_ALL_NODES(node, node._processNode()); }
void Layer::iFixedProcess() { _FOR_ALL_NODES(node, node._fixedProcessNode()); }

#undef _FOR_ALL_NODES

void Layer::_disconnect(Node::ID id) noexcept { _nodes.remove(id); }

void Layer::addNode(std::unique_ptr<Node> node, bool is_active) noexcept
{
    if (_nodes.size() == _nodes.capacity()) [[unlikely]] ZPERFORMANCE(
        "Layer '{}' size exceeding capacity of '{}'",
        getName(), _nodes.size()
    );

    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Node '{}' added to Layer '{}'",
        node->getName(), getName()
    );

    const Node::ID NODE_ID = node->getID();

    ZVERIFY(
        _nodes.add(std::move(node)),
        "Failed to add Node #{} into Layer '{}'", NODE_ID, getName()
    );

    if (is_active) getNodeHandle(NODE_ID).getNode().setActive(true);
}

void Layer::removeAllNodes() noexcept
{
    _nodes.clear();
    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "All Nodes removed from Layer '{}'", getName()
    );
}

[[nodiscard]]
misc::LayerNodeHandle Layer::getNodeHandle(Node::ID node_id) noexcept
{
    return misc::LayerNodeHandle { *this, node_id };
}

void Layer::forAllNodes(const std::function<void(Node&)>& function) noexcept
{
    for (std::unique_ptr<Node>& node : _nodes) function(*node.get());
}

} // namespace dull::process
