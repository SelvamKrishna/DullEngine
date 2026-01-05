#pragma once

#include "engine/misc/identification.hpp"
#include "engine/misc/processor.hpp"

namespace dull::process {

struct NodeTag {};

// =======================
// Base Node class
// =======================
class Node : private misc::IProcessor, public misc::Identified<NodeTag> {
    friend core::App;
    friend class Layer;

    friend void _startNode(Node& node) noexcept;
    friend void _processNode(Node& node) noexcept;
    friend void _fixedProcessNode(Node& node) noexcept;

private:
    bool _is_active {false}; //< The `Layer` will auto set default values

    void _startNode() noexcept;
    void _processNode() noexcept;
    void _fixedProcessNode() noexcept;

protected:
    void iStart()        override {}
    void iProcess()      override {}
    void iFixedProcess() override {}

public:
    bool is_process       {true}; // Whether to call _update()
    bool is_fixed_process {true}; // Whether to call _fixedUpdate()

    Node(std::string name);
    virtual ~Node() = default;

    [[nodiscard]]
    constexpr bool isActive() const noexcept { return _is_active; }

    // Calls the Node::_start() function if it is made alive
    void setActive(bool value) noexcept;
};

} // namespace dull::process
