#pragma once

#include <string>
#include <string_view>

/// Building block of the application;
/// Node in active scene are processed every frame;
/// VIRTUAL: Must be derived to create a custom node;
class Node {
	friend class Scene;

private:
	virtual void _init() {}
	virtual void _update() {}
	virtual void _fixedUpdate() {}

protected:
	std::string _name;

public:
	bool is_active { false };
	bool is_updating { true };
	bool is_fixed_updating { true };

	explicit Node(std::string name);
	virtual ~Node() = default;

	Node(const Node&) = delete;
	Node(Node&&) noexcept = default;
	Node& operator=(const Node&) = delete;
	Node& operator=(Node&&) noexcept = default;

	[[nodiscard]] constexpr std::string_view name() const noexcept { return _name; }
};
