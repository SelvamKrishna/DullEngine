#include "engine/core/app.hpp"
#include "engine/core/node.hpp"

namespace dull::core {

    void Node::setActive(bool value) noexcept
    {
        if (value == _is_active) return; // No changes made

        if (
            // Inside an active layer
            DULL_HANDLE.scene_sys.getCurrentScene()->isLayerActive(_layer_name) ||
            // Is being deactivated. Node can be set inactive even when not alive
            !value
        ) _is_active = value;

        if (_is_active) _start(); // Must be inside an alive Layer
    }

} // namespace dull::core
