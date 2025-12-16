#include "engine/core/app.hpp"
#include "engine/core/node.hpp"

namespace dull::core {

    void Node::setActive(bool value) noexcept
    {
        if (value == _is_active) return;

        if (
            _is_active = value; value && // Activated
            DULL_HANDLE.scene_sys->getCurrentScene()->isLayerActive(_layer_name) // In active layer
        ) _start();
    }

} // namespace dull::core
