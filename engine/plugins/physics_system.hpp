#pragma once

/// System to handle all application physics logic;
/// VIRTUAL: Need to be derived to create a custom system;
class PhysicsSystem {
	friend class App;

private:
	virtual void _init() {}
	virtual void _update() {}

public:
	explicit PhysicsSystem() = default;
	virtual ~PhysicsSystem() = default;
};