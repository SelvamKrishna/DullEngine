#pragma once

/// Base class for managing rendering logic.
/// Supports custom implementations via inheritance.
class RenderSystem {
    friend class App;

private:
    static void _drawNull() noexcept;

    virtual void _init() {}
    virtual void _update();

public:
    RenderSystem() = default;
    virtual ~RenderSystem() = default;

    RenderSystem(const RenderSystem &) = delete;
    RenderSystem(RenderSystem &&) = delete;
    RenderSystem &operator=(const RenderSystem &) = delete;
    RenderSystem &operator=(RenderSystem &&) = delete;
};