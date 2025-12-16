#pragma once

#include <string_view>

namespace dull::core {

// =======================
// Base Node class
// =======================
class Node {
    friend class Layer;

private:
    std::string_view _layer_name; //< Name of the owner `Layer`
    bool _is_active {false};      //< The `Layer` will auto set default values

/*
    - A node is considered 'alive' if it is active and inside an active layer
*/

    // DO NOT directly call `Node::_start()` use `Node::setActive(true)` instead.
    // Called when 'alive'
    virtual void _start() {}

    // Called every frame while 'alive' & 'is_process'
    virtual void _update() {}

    // Called every fixed interval while 'alive' & 'is_fixed_process'
    virtual void _fixedUpdate() {}

public:
    bool is_process       {true}; // Whether to call _update()
    bool is_fixed_process {true}; // Whether to call _fixedUpdate()

    Node() = default;
    virtual ~Node() = default;

    [[nodiscard]]
    constexpr bool isActive() const noexcept { return _is_active; }

    void setActive(bool value) noexcept;

    [[nodiscard]]
    const std::string_view getOwnerLayer() const noexcept { return _layer_name; }
};

} // namespace dull::core
