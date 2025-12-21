#pragma once

#include <cstdint>

#include "engine/system/time_sys.hpp"

// Forward Declaration

namespace dull::sys { class EventSystem; };

namespace dull::core {

class SceneSystem;
class LayerBuffer;
class SceneBuffer;

// =======================
// A enum to keep track of the app state
// =======================
enum class ProgramState : uint8_t { Initial, Process, Conclude, };

struct HandleCtx final {
    sys::TimeSystem& time_sys; //< Stores all time related data
    sys::EventSystem& event_sys; //< Handles all event related logic
    SceneSystem& scene_sys; //< Handles all scene related logic
    LayerBuffer& layer_buf; //< Stores all layer related data
    SceneBuffer& scene_buf; //< Stores all scene related data
    double& delta_time; //< Reference to delta time
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

    explicit Handle(HandleCtx ctx) : ctx {ctx} {}
    ~Handle() = default;

    void _init() noexcept;
    void _setState(ProgramState new_state) noexcept { _state = new_state; }

public:
    HandleCtx ctx;

    [[nodiscard]]
    const ProgramState& getProgramState() const noexcept { return _state; }

    [[nodiscard]]
    constexpr bool isStarting() const noexcept { return _state == ProgramState::Initial; }

    [[nodiscard]]
    constexpr bool isRunning() const noexcept { return _state == ProgramState::Process; }

    [[nodiscard]]
    constexpr bool isQuitting() const noexcept { return _state == ProgramState::Conclude; }
};

} // namespace dull::core

