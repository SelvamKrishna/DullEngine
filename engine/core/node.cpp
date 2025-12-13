#include "engine/core/app.hpp"
#include "engine/core/node.hpp"

namespace dull::core {

    void Node::setActive(bool value) noexcept
    {
        if (value == _is_active) return;

        if (
            _is_active = value; value &&
            DULL_HANDLE.sceneSystem().current_scene.isLayerActive(_layer_name)
        ) _start();
    }

} // namespace dull::core
