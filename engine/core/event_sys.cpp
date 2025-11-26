#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/core/event_sys.hpp"

#include <atomic>

namespace dull::core {

uint64_t Event::bind(Event::Callback callback) {
  return App::instance().getEventBus().bind(_name, std::move(callback));
}

void Event::unbind(uint64_t id) {
  return App::instance().getEventBus().unbind(_name, id);
}

void Event::emit() const noexcept {
  return App::instance().getEventBus().emit(_name);
}

uint64_t EventBus::bind(std::string_view event_name, Event::Callback callback) {
  std::unique_lock lock {_mutex};

  static std::atomic<uint64_t> s_next {1};
  uint64_t id = s_next++;

  _listeners[std::string{event_name}].emplace_back(Listener{id, std::move(callback)});
  ZLOGI_IF(config::SHOULD_LOG_EVENT_SYS)
    << "Event bind: " << event_name << " <-> Listener (" << id << ")";

  return id;
}

void EventBus::unbind(std::string_view event_name, uint64_t id) {
  std::shared_lock lock {_mutex};

  auto it = _listeners.find(event_name);
  if (it == _listeners.end()) {
    ZLOGW_IF(config::SHOULD_LOG_EVENT_SYS)
      << "Event unbind (NOT FOUND): " << event_name << " <-> Listener (ID: " << id << ")";
    return;
  }

  std::erase_if(it->second, [&id](const Listener &listener) { return listener.id == id; });
  ZLOGI_IF(config::SHOULD_LOG_EVENT_SYS)
    << "Event unbind: " << event_name << " <-> Listener (ID: " << id << ")";

  if (it->second.empty()) {
    _listeners.erase(it);
    ZLOGI_IF(config::SHOULD_LOG_EVENT_SYS) << "Event erase: " << event_name << ", has no binded listerners";
  }
}

void EventBus::emit(const Event &event) const noexcept {
  if (auto it = _listeners.find(event.getName()); it != _listeners.end()) {
    ZLOGI_IF(config::SHOULD_LOG_EVENT_SYS) << "Event emit : " << event.getName();
    for (const auto &LISTENER : it->second) LISTENER.callback(event);
    return;
  }

  ZLOGW_IF(config::SHOULD_LOG_EVENT_SYS) << "Event emit (NOT FOUND) : " << event.getName();
}

} // namespace dull::core
