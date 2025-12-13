#pragma once

#include "engine/core/event_bus.hpp"
#include "engine/core/scene.hpp"

#include <cstdint>

namespace dull::core {

// =======================
// A enum to keep track of the app state
// =======================
enum class ProgramState : uint8_t {
    Initial,
    Process,
    Conclude,
};

// =======================
// Access provider to core systems
// =======================
// This prevents direct access to App's internals
// and allows controlled exposure of functionality
class Handle final {
    friend class App;

private:
    ProgramState _state = ProgramState::Initial;

    constexpr Handle(Handle&&)                 noexcept = delete;
    constexpr Handle(const Handle&)            noexcept = delete;
    constexpr Handle& operator=(Handle&&)      noexcept = delete;
    constexpr Handle& operator=(const Handle&) noexcept = delete;

    explicit Handle() = default;
    ~Handle() = default;

    void _init() noexcept;
    void _setState(ProgramState new_state) noexcept { _state = new_state; }

public:
    SceneSystem& sceneSystem() noexcept;
    const SceneSystem& sceneSystem() const noexcept;

    EventBus& eventBus() noexcept;
    const EventBus& eventBus() const noexcept;
};

} // namespace dull::core

