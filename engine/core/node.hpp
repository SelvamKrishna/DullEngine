#pragma once

#include "engine/misc/processor.hpp"

#include <string_view>

namespace dull::core {

// =======================
// Base Node class
// =======================
class Node : private misc::IProcessor {
    friend class Layer;

private:
    std::string_view _layer_name; //< Name of the owner `Layer`
    bool _is_active {false};      //< The `Layer` will auto set default values

    // DO NOT directly call `Node::iStart()` use `Node::setActive(true)` instead.
    void iStart() override {}
    void iProcess() override {}
    void iFixedProcess() override {}

public:
    bool is_process       {true}; // Whether to call _update()
    bool is_fixed_process {true}; // Whether to call _fixedUpdate()

    Node() = default;
    virtual ~Node() = default;

    [[nodiscard]]
    constexpr bool isActive() const noexcept { return _is_active; }

    // Calls the Node::_start() function if it is made alive
    void setActive(bool value) noexcept;

    // Name of the Owning Layer
    [[nodiscard]]
    const std::string_view getLayer() const noexcept { return _layer_name; }
};

} // namespace dull::core
