#include "engine/core/app.hpp"
#include "engine/plugins/signal_system.hpp"

#include <algorithm>
#include <format>
#include <memory>

Observer::~Observer() { detachAllSignal(); }

void Observer::attachSignal(std::string_view signal) noexcept {
	if (signal.empty()) {
		ErrorCtx{"Attach signal to observer"}
			.failFallback("Signal can't be empty");
	} else SIGNAL_SYS.bindObserver(weak_from_this(), signal);
}

void Observer::detachSignal(std::string_view signal) noexcept {
	if (signal.empty()) {
		ErrorCtx{"Detach signal from observer"}
			.failFallback("Signal can't be empty");
	} else SIGNAL_SYS.unbindObserver(weak_from_this(), signal);
}

void Observer::detachAllSignal() noexcept { SIGNAL_SYS.unbindObserver(weak_from_this(), ""); }

void SignalSystem::_removeObserver(const Observer* observer_ptr, std::string_view signal, ErrorCtx& err) {
	auto signal_map { _signal_links.find(signal) };

	if (signal_map == _signal_links.end()) {
		err.failFallback("Signal not found");
		return;
	}

	auto& observers_vec = signal_map->second;
	auto it = std::ranges::find_if(
		observers_vec,
		[observer_ptr](const std::weak_ptr<Observer>& weak_observer) {
			auto shared_observer { weak_observer.lock() };
			return shared_observer.get() == observer_ptr;
		}
	);

	if (it == observers_vec.end()) err.failFallback("Observer not found");
	else observers_vec.erase(it);

	#ifdef DULL_DBG_SIGNALS
	DULL_INFO("[SIGNAL SYSTEM] Observer removed from Signal '{}'", signal);
	#endif
}

void SignalSystem::bindObserver(const std::weak_ptr<Observer>& observer, std::string_view signal) noexcept {
	std::lock_guard<std::mutex> lock(_mutex);

	if (observer.expired()) {
		ErrorCtx(std::format("Bind observer to signal '{}'", signal))
		.failFallback("Expired observer provided");
		return;
	}

	_signal_links.find(signal)->second.emplace_back(observer);

	#ifdef DULL_DBG_SIGNALS
	DULL_INFO("[SIGNAL SYSTEM] Observer binded to Signal '{}'", signal);
	#endif
}

void SignalSystem::unbindObserver(const std::weak_ptr<Observer>& observer, std::string_view signal) noexcept {
	std::lock_guard<std::mutex> lock(_mutex);

	if (observer.expired()) return;

	ErrorCtx err(std::format("Unbinding observer from signal '{}'", signal));

	const Observer* const OBSERVER_PTR { observer.lock().get() };

	if (!signal.empty()) {
		_removeObserver(OBSERVER_PTR, signal, err);
		return;
	}

	for (const auto& [SIGNAL_IT, _] : _signal_links) {
		_removeObserver(OBSERVER_PTR, SIGNAL_IT, err);
	}
}

void SignalSystem::emitSignal(std::string_view signal) noexcept {
	std::vector<std::shared_ptr<Observer>> to_call;

    [this, &signal, &to_call] {
        std::lock_guard lock(_mutex);

        auto it { _signal_links.find(signal) };
        if (it == _signal_links.end()) return;

        to_call.reserve(it->second.size());
        for (auto& weak_observer : it->second) {
            if (auto shared_observer = weak_observer.lock())
                to_call.push_back(shared_observer);
        }
    } ();

    for (auto& observer : to_call) {
        if (!observer->_callback) {
            ErrorCtx(std::format("Emit Signal '{}'", signal))
                .failFallback("Null callback function for observer");
            continue;
        }
        observer->_callback();
    }

    #ifdef DULL_DBG_SIGNALS
    DULL_INFO("[SIGNAL SYSTEM] Signal '{}' emitted", signal);
    #endif
}

void SignalSystem::cleanupExpiredObservers() noexcept {
	#ifdef DULL_DBG_SIGNALS
	DULL_INFO("[SIGNAL SYSTEM] Cleaning all expired observers");
	#endif

	for (auto& [_, observers_vec] : _signal_links) {
		for (auto it { observers_vec.begin() }; it != observers_vec.end(); it++) {
			if (!it->expired()) continue;
			observers_vec.erase(it);
		}
		observers_vec.shrink_to_fit();
	}
}