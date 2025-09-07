#pragma once

/// Global node like class which is directly owned by the application
/// VIRTUAL: Derive to create your own custom global system
class GlobalSystem {
	friend class App;
private:
	virtual void _init() {}
	virtual void _update() {}
	virtual void _fixedUpdate() {}

public:
	explicit GlobalSystem() = default;
	virtual ~GlobalSystem() = default;
};