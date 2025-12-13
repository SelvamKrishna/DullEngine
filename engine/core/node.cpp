#include "engine/core/app.hpp"
#include "engine/core/node.hpp"

namespace dull::core {

    void Node::setActive(bool value) noexcept
    {
        if (value == _is_active) return;

        const bool WAS_ACTIVE = _is_active;
        _is_active = value;

        if (
            !WAS_ACTIVE && // Inactive before and now active
            DULL_HANDLE.sceneSystem().isLayerActive(_layer_name) // Inside active layer
        ) _start();
    }

} // namespace dull::core
