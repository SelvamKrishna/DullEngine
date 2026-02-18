#pragma once

#include "engine/system/time_system.hpp"

#include <cstdint>

namespace dull::core {

// ---
// Enumeration of all possible application states
// ---
enum struct ProgramState : uint8_t { Opening, Running, Closing, };

// ---
// Contains references of all application systems
// ---
struct HandleContext final {
    system::TimeSystem& timeSystem;
};

// ---
// Global access provider for all application systems
// ---
struct Handle final {
    friend struct App;

private:
    ProgramState _programState = ProgramState::Opening;

    constexpr Handle(Handle&&)                 noexcept = delete;
    constexpr Handle(const Handle&)            noexcept = delete;
    constexpr Handle& operator=(Handle&&)      noexcept = delete;
    constexpr Handle& operator=(const Handle&) noexcept = delete;

    explicit Handle(const HandleContext& context) : context {context} {}
    ~Handle() = default;

    void _SetState(ProgramState newProgramState) noexcept { _programState = newProgramState; }

public:
    HandleContext context;

    [[nodiscard]] constexpr bool IsOpening() const noexcept { return _programState == ProgramState::Opening; }
    [[nodiscard]] constexpr bool IsRunning() const noexcept { return _programState == ProgramState::Running; }
    [[nodiscard]] constexpr bool IsClosing() const noexcept { return _programState == ProgramState::Closing; }
};

} // namespace dull::core

