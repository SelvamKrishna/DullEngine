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
    Observer();
    virtual ~Observer();

    Observer(const Observer &) = delete;
    Observer &operator=(const Observer &) = delete;
    Observer(Observer &&) = delete;
    Observer &operator=(Observer &&) = delete;

    void bindCallback(std::function<void()> callback);
    void attachSignal(std::string_view signal);
    void detachSignal(std::string_view signal);
};

/// UNTESTED:
class SignalSystem {
private:
    std::unordered_map<std::string, std::vector<std::weak_ptr<Observer>>> _signal_links;
    std::mutex _mutex;

    void _cleanupExpiredObserversFromSignal(const std::string &signal);
    void _cleanupExpiredObservers();

    void _removeObserver(const Observer *observer_ptr, const std::string &signal, ErrorCtx &err);

public:
    SignalSystem() = default;
    ~SignalSystem() = default;

    SignalSystem(const SignalSystem &) = delete;
    SignalSystem(SignalSystem &&) = delete;
    SignalSystem &operator=(const SignalSystem &) = delete;
    SignalSystem &operator=(SignalSystem &&) = delete;

    void bindObserver(const std::weak_ptr<Observer> &observer, const std::string &signal);
    void unbindObserver(const std::weak_ptr<Observer> &observer, const std::string &signal = "");
    void emitSignal(const std::string &signal);
};