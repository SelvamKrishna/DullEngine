#pragma once

#include <cstdint>

#include "engine/config.hpp"
#include "engine/system/audio_system.hpp"
#include "engine/system/event_system.hpp"
#include "engine/system/render_system.hpp"
#include "engine/system/time_system.hpp"

namespace dull::core {

// =======================
// A enum to keep track of the app state
// =======================
enum class ProgramState : uint8_t { Initialization, Processing, ShuttingDown, };

struct HandleContext final {
    system::AudioSystem&  audio_sys;   //< Handles all audio related logic
    system::EventSystem&  event_sys;   //< Handles all event related logic
    system::RenderSystem& render_sys;  //< Handles all rendering logic
    system::TimeSystem&   time_sys;    //< Stores all time related data
    config::Processor&    processor;   //< Handles all logic processing
};

// =======================
// Global Access provider to core systems
// =======================
class Handle final {
    friend class App;

private:
    ProgramState _state = ProgramState::Initialization;

    constexpr Handle(Handle&&)                 noexcept = delete;
    constexpr Handle(const Handle&)            noexcept = delete;
    constexpr Handle& operator=(Handle&&)      noexcept = delete;
    constexpr Handle& operator=(const Handle&) noexcept = delete;

    explicit Handle(HandleContext ctx) : ctx {ctx} {}
    ~Handle() = default;

    void _setState(ProgramState new_state) noexcept { _state = new_state; }

public:
    HandleContext ctx;

    [[nodiscard]]
    constexpr bool isStarting() const noexcept { return _state == ProgramState::Initialization; }

    [[nodiscard]]
    constexpr bool isRunning() const noexcept { return _state == ProgramState::Processing; }

    [[nodiscard]]
    constexpr bool isQuitting() const noexcept { return _state == ProgramState::ShuttingDown; }
};

} // namespace dull::core

