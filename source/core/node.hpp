#pragma once

#include <string>

/// A base class for all processing elements in the application.
class Node {
    friend class Scene;

private:
    virtual void _init() {}
    virtual void _update() {}
    virtual void _fixedUpdate() {}

protected:
    /// TODO: Add a better method of identification for nodes.
    std::string _name;
    bool _is_active = true;

public:
    explicit Node(std::string name);
    virtual ~Node() = default;

    Node(const Node &) = delete;
    Node(Node &&) noexcept = default;
    Node &operator=(const Node &) = delete;
    Node &operator=(Node &&) noexcept = default;

    void setActive(bool node_state) noexcept { _is_active = node_state; }

    [[nodiscard]] const std::string &name() const noexcept { return _name; }
    [[nodiscard]] bool isActive() const noexcept { return _is_active; }
};