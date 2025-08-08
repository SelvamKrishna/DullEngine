#pragma once

#include "../utils/debug.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

/// UNTESTED:
class Observer : public std::enable_shared_from_this<Observer> {
    friend class SignalSystem;

private:
    std::function<void()> _callback;

public:
    explicit Observer(std::function<void()> callback) : _callback(std::move(callback)) {}
    ~Observer();

    Observer(const Observer &) = delete;
    Observer &operator=(const Observer &) = delete;
    Observer(Observer &&) = delete;
    Observer &operator=(Observer &&) = delete;

    void attachSignal(std::string_view signal);
    void detachSignal(std::string_view signal);
    void detachAllSignal();
};

/// UNTESTED:
class SignalSystem {
private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<Observer>>> _signal_links;
    std::mutex _mutex;

    void _removeObserver(const Observer *observer_ptr, std::string_view signal, ErrorCtx &err);

public:
    SignalSystem() = default;
    ~SignalSystem() = default;

    SignalSystem(const SignalSystem &) = delete;
    SignalSystem &operator=(const SignalSystem &) = delete;
    SignalSystem(SignalSystem &&) = delete;
    SignalSystem &operator=(SignalSystem &&) = delete;

    void bindObserver(const std::weak_ptr<Observer> &observer, std::string_view signal);
    void unbindObserver(const std::weak_ptr<Observer> &observer, std::string_view signal = "");
    void emitSignal(std::string_view signal);

    void cleanupExpiredObservers();
};