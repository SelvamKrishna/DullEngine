#include "engine/config.hpp"
#include "engine/process/node_handle.hpp"
#include "engine/process/layer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::process {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_SCENE_SYS)

void LayerNodeHandle::removeFromLayer() noexcept
{
    _IF_LOG ZINFO(
        "Node '{}' removed from Layer '{}'",
        getNode().getName(), _layer.getName()
    );

    _layer._nodes.erase(_node_it);
}

[[nodiscard]]
std::unique_ptr<Node> LayerNodeHandle::extractFromLayer() noexcept
{
    _IF_LOG ZINFO(
        "Node '{}' extracted from Layer '{}'",
        getNode().getName(), _layer.getName()
    );

    std::unique_ptr<Node> node {std::move(_node_it->get())};
    _layer._disconnect(_node_it);

    return node;
}

#undef _IF_LOG

} // namespace dull::process
