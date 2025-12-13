#pragma once

#include <vendor/zutils/tools.hpp>

namespace dull::core {

// =======================
// Base Node class (OVERRIDABLE)
// =======================
class Node {
    friend class Layer;

private:
    std::string_view _layer_name;
    bool _is_active {true};

/*
    A node is considered 'alive' if it is active and inside an active layer
*/

    // Called by layer when the Node becomes 'alive'
    virtual void _start() {}

    // Called by the layer every frame while 'alive'
    virtual void _update() {}

    // Called by the layer every fixed update while 'alive'
    virtual void _fixedUpdate() {}

public:
    bool is_process       {true};
    bool is_fixed_process {true};

    Node() = default;
    virtual ~Node() = default;

    [[nodiscard]]
    constexpr bool isActive() const noexcept { return _is_active; }

    void setActive(bool value) noexcept;
};

} // namespace dull::core
