#pragma once

#include "engine/core/event_bus.hpp"
#include "engine/core/scene_system.hpp"

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
// Global Access provider to core systems
// =======================
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
    EventBus*    event_bus = nullptr;
    SceneSystem* scene_sys = nullptr;

    [[nodiscard]]
    const ProgramState& getProgramState() const noexcept { return _state; }
};

} // namespace dull::core

