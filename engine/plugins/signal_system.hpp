#pragma once

#include "../utils/debug.hpp"
#include "../utils/misc.hpp"

#include <functional>
#include <memory>
#include <mutex>
#include <string_view>

/// Observes signals and calls callback function when triggered;
class Observer : public std::enable_shared_from_this<Observer> {
	friend class SignalSystem;

private:
	std::function<void()> _callback;

public:
	explicit Observer(std::function<void()> callback) : _callback(std::move(callback)) {}
	~Observer();

	Observer(const Observer&) = delete;
	Observer& operator=(const Observer&) = delete;
	Observer(Observer&&) = delete;
	Observer& operator=(Observer&&) = delete;

	void attachSignal(std::string_view signal) noexcept;
	void detachSignal(std::string_view signal) noexcept;
	void detachAllSignal() noexcept;
};

/// Handles all (signal - observer) relations
/// TODO: Emit Default signals EX: scene-change, node-added, node-removed;
/// TODO: Emit signals carrying data EX: (node-added: "NODE NAME");
class SignalSystem {
	friend class App;

private:
	std::unordered_map<
		std::string,
		std::vector<std::weak_ptr<Observer>>,
		Misc::TransparentStringHash,
		Misc::TransparentStringEqualTo
	> _signal_links;

	std::mutex _mutex;

	explicit SignalSystem() = default;
	void _removeObserver(const Observer* observer_ptr, std::string_view signal, ErrorCtx& err);

public:
	~SignalSystem() = default;

	SignalSystem(const SignalSystem&) = delete;
	SignalSystem& operator=(const SignalSystem&) = delete;
	SignalSystem(SignalSystem&&) = delete;
	SignalSystem& operator=(SignalSystem&&) = delete;

	void bindObserver(const std::weak_ptr<Observer>& observer, std::string_view signal) noexcept;
	void unbindObserver(const std::weak_ptr<Observer>& observer, std::string_view signal = "") noexcept;
	void emitSignal(std::string_view signal) noexcept;

	void cleanupExpiredObservers() noexcept;
};