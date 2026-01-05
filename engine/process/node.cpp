#include "engine/core/app.hpp"
#include "engine/process/node.hpp"

namespace dull::process {

void Node::_startNode()        noexcept { if (isActive())       iStart(); }
void Node::_processNode()      noexcept { if (is_process)       iProcess(); }
void Node::_fixedProcessNode() noexcept { if (is_fixed_process) iFixedProcess(); }

Node::Node(std::string name) : misc::Identified<NodeTag> {name} {}

void Node::setActive(bool value) noexcept
{
    if (value == _is_active) return;
    _is_active = value;
    if (_is_active && DULL_HANDLE.isRunning()) iStart();
}

} // namespace dull::core
