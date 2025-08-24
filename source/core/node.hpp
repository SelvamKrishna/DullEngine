#pragma once

#include <string>
#include <string_view>

class Node {
	friend class Scene;

private:
	virtual void _init() {}
	virtual void _update() {}
	virtual void _fixedUpdate() {}

protected:
	std::string _name;
	bool _is_active = false;
	bool _is_updating = true;
	bool _is_fixed_updating = true;

public:
	explicit Node(std::string name);
	virtual ~Node() = default;

	Node(const Node&) = delete;
	Node(Node&&) noexcept = default;
	Node& operator=(const Node&) = delete;
	Node& operator=(Node&&) noexcept = default;

	constexpr void setActive(bool flag) noexcept { _is_active = flag; }
	constexpr void setUpdate(bool flag) noexcept { _is_updating = flag; }
	constexpr void setFixedUpdate(bool flag) noexcept { _is_fixed_updating = flag; }

	[[nodiscard]] constexpr std::string_view name() const noexcept { return _name; }
	[[nodiscard]] constexpr bool isActive() const noexcept { return _is_active; }
	[[nodiscard]] constexpr bool isUpdating() const noexcept { return _is_updating; }
	[[nodiscard]] constexpr bool isFixedUpdating() const noexcept { return _is_fixed_updating; }
};