#pragma once

#include <string>

namespace dull::core {

class Node {
    friend class Layer;

private:
    std::string _name;
    bool _is_active {true};

    virtual void _start() {}
    virtual void _update() {}
    virtual void _fixedUpdate() {}

public:
    Node() = delete;

    explicit Node(std::string_view name) : _name{name} {}
    virtual ~Node() = default;

    [[nodiscard]]
    constexpr std::string& getName() noexcept { return _name; }

    [[nodiscard]]
    constexpr bool isActive() const noexcept { return _is_active; }

    constexpr void setActive(bool value) noexcept { _is_active = value; }
};

} // namespace dull::core
