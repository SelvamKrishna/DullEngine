#include "signal_system.hpp"

#include "../core/app.hpp"
#include "../utils/debug.hpp"

#include <algorithm>
#include <format>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

void Observer::bindCallback(std::function<void()> callback) {
    if (_callback != nullptr) {
        ErrorCtx("Bind callback to observer").failFallback("Observer callback already set");
    }

    _callback = std::move(callback);
}

void Observer::attachSignal(std::string_view signal) {
    SIGNAL_SYS.bindObserver(weak_from_this(), std::string(signal));
}

void Observer::detachSignal(std::string_view signal) {
    SIGNAL_SYS.unbindObserver(weak_from_this(), std::string(signal));
}

void SignalSystem::_cleanupExpiredObserversFromSignal(const std::string &signal) {
    DULL_WARN("Cleaning up expired observers from '{}'.", signal);

    auto &observer_list = _signal_links.at(signal);

    if (observer_list.empty()) {
        return;
    }

    for (auto it = observer_list.begin(); it != observer_list.end(); it++) {
        if (it->expired()) {
            observer_list.erase(it);
        }
    }
}

void SignalSystem::_cleanupExpiredObservers() {
    DULL_WARN("Cleaning up expired observers.");

    for (auto &[signal, observer_list] : _signal_links) {
        _cleanupExpiredObserversFromSignal(signal);
        observer_list.shrink_to_fit();
    }
}

void SignalSystem::_removeObserver(const Observer *observer_ptr, const std::string &signal, ErrorCtx &err) {
    auto &observer_list = _signal_links.at(signal);

    if (observer_list.empty()) {
        err.failFallback("No observers in signal");
        return;
    }

    auto it = std::ranges::find_if(observer_list, [observer_ptr](const auto &observer_ref) {
        if (auto observer_shared = observer_ref.lock()) {
            return observer_shared.get() == observer_ptr;
        }

        return false;
    });

    if (it == observer_list.end()) {
        err.failFallback("Not found");
        return;
    }

    observer_list.erase(it);
}

void SignalSystem::bindObserver(const std::weak_ptr<Observer> &observer, const std::string &signal) {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Binding observer to '{}'", signal));

    if (observer.expired()) {
        err.failFallback("Observer expired");
        return;
    }

    const auto *const observer_ptr = observer.lock().get();

    std::vector<std::weak_ptr<Observer>> &observer_list = _signal_links.at(signal);
    auto it =
        std::ranges::find_if(observer_list, [observer_ptr](const std::weak_ptr<Observer> &observer_ref) {
            if (auto observer_shared = observer_ref.lock()) {
                return observer_shared.get() == observer_ptr;
            }

            return false;
        });

    if (it != observer_list.end()) {
        err.failFallback("Observer already exist");
        return;
    }

    _signal_links[signal].emplace_back(observer);
    DULL_INFO("Observer binded with '{}'", signal);
}

void SignalSystem::unbindObserver(const std::weak_ptr<Observer> &observer, const std::string &signal) {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Unbinding observer from '{}'", signal));

    if (observer.expired()) {
        err.failFallback("Observer expired");
        _cleanupExpiredObserversFromSignal(signal);
        return;
    }

    const auto *const observer_ptr = observer.lock().get();

    if (signal.empty()) [[unlikely]] {
        for (auto &[signal_it, _] : _signal_links) {
            _removeObserver(observer_ptr, signal_it, err);
        }
    } else {
        _removeObserver(observer_ptr, signal, err);
    }
}

void SignalSystem::emitSignal(const std::string &signal) {
    std::lock_guard<std::mutex> lock(_mutex);

    auto &observer_list = _signal_links.at(signal);

    if (observer_list.empty()) {
        return;
    }

    _cleanupExpiredObserversFromSignal(signal);

    for (auto &observer_ref : observer_list) {
        if (auto observer_shared = observer_ref.lock()) {
            if (observer_shared->_callback == nullptr) {
                ErrorCtx(std::format("Emit signal '{}'", signal)).failFallback("Unbinded observer callback");
                continue;
            }

            observer_shared->_callback();
        }
    }
}