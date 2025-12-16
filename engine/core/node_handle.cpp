#include "engine/config.hpp"
#include "engine/core/node_handle.hpp"
#include "engine/core/layer.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_LAYER_SYS)

void NodeHandle::removeFromLayer() noexcept
{
    _IF_LOG ZINFO("Node '{}' removed from Layer '{}'", _node_it->name, _layer._name);
    _layer._nodes.erase(_node_it);
}

[[nodiscard]]
std::unique_ptr<Node> NodeHandle::extractFromLayer() noexcept
{
    _IF_LOG ZINFO("Node '{}' extracted from Layer '{}'", _node_it->name, _layer._name);

    std::unique_ptr<Node> node = {std::move(_node_it->uptr)};
    Layer::_disconnect(_node_it);
    _layer._nodes.erase(_node_it);

    return node;
}

[[nodiscard]]
const std::string_view NodeHandle::getName() const noexcept { return _node_it->name; }

[[nodiscard]]
std::unique_ptr<Node>& NodeHandle::getNode() noexcept { return _node_it->uptr; }

#undef _IF_LOG

} // namespace dull::core
