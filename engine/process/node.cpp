#include "engine/process/node.hpp"

namespace dull::process {

Node::Node(std::string name) : misc::Identified<NodeTag> {name} {}

void Node::setActive(bool value) noexcept
{
    if (value == _is_active) return;
    _is_active = value;
    if (_is_active) iStart();
}

} // namespace dull::core
