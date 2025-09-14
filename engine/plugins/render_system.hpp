#pragma once

/// System to handle all draw calls and draw logics
/// VIRTUAL: Must be derived to create a custom render system
class RenderSystem {
	friend class App;

private:
	static void _drawNull() noexcept;

	virtual void _init() {}
	virtual void _draw() {}

	void _update();

public:
	explicit RenderSystem() = default;
	virtual ~RenderSystem() = default;

	RenderSystem(const RenderSystem&) = delete;
	RenderSystem(RenderSystem&&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;
	RenderSystem& operator=(RenderSystem&&) = delete;
};