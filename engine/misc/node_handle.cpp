#include "engine/config.hpp"
#include "engine/process/layer.hpp"
#include "engine/misc/node_handle.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

[[nodiscard]]
process::Node* LayerNodeHandle::findNode() noexcept
{
    process::Node* node_ptr = _layer.getAllNodes().find(_node_id);
    ZASSERT(
        node_ptr != nullptr,
        "Node with ID '{}' not found in Layer ''", _node_id, _layer.getName()
    );
    return node_ptr;
}

[[nodiscard]]
process::Node& LayerNodeHandle::getNode() noexcept { return *findNode(); }

void LayerNodeHandle::removeFromLayer() noexcept
{
    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Node '{}' removed from Layer '{}'",
        getNode().getName(), _layer.getName()
    );

    _layer.getAllNodes().remove(_node_id);
}

[[nodiscard]]
std::unique_ptr<process::Node> LayerNodeHandle::extractFromLayer() noexcept
{
    if constexpr (config::SHOULD_LOG_PROCESS_SYS) ZINFO(
        "Node '{}' extracted from Layer '{}'",
        getNode().getName(), _layer.getName()
    );

    std::unique_ptr<process::Node> node {std::move(findNode())};
    _layer.getAllNodes().remove(_node_id);

    return node;
}

#undef _IF_LOG

} // namespace dull::misc
