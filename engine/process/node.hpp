#pragma once

#include "engine/misc/processor.hpp"

#include <string>

namespace dull::process {

// =======================
// Base Node class
// =======================
class Node : protected misc::IProcessor {
    friend core::App;
    friend class Layer;

private:
    std::string _name;       //< Node name (UNIQUE within Layer)
    bool _is_active {false}; //< The `Layer` will auto set default values

protected:
    // DO NOT directly call `Node::iStart()` use `Node::setActive(true)` instead.
    void iStart() override {}
    void iProcess() override {}
    void iFixedProcess() override {}

public:
    bool is_process       {true}; // Whether to call _update()
    bool is_fixed_process {true}; // Whether to call _fixedUpdate()

    Node(std::string name) : _name {name} {}
    virtual ~Node() = default;

    [[nodiscard]]
    constexpr std::string_view getName() const noexcept { return _name; }

    [[nodiscard]]
    constexpr bool isActive() const noexcept { return _is_active; }

    // Calls the Node::_start() function if it is made alive
    void setActive(bool value) noexcept;
};

} // namespace dull::process
