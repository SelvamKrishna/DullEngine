#pragma once

#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

/// INCOMPLETE:
/// Observer for signal calls
class Observer {
    friend class SignalSystem;

private:
    /// TODO: Behaviour should be modifiable by node
    void _onSignalEmit() {}

public:
    void attachSignal(std::string_view signal);
    void detachSignal(std::string_view signal);
};

/// INCOMPLETE:
/// Handles signals and observer logic
/// TODO: Thread safety
class SignalSystem {
    friend class App;

private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<Observer>>> _signal_links;

    explicit SignalSystem() = default;
    ~SignalSystem() = default;

public:
    SignalSystem(const SignalSystem &) = delete;
    SignalSystem(SignalSystem &&) = delete;
    SignalSystem &operator=(const SignalSystem &) = delete;
    SignalSystem &operator=(SignalSystem &&) = delete;

    void emitSignal(std::string signal) noexcept;
    void bindObserver(Observer *observer, std::string signal) noexcept;
};