#pragma once

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