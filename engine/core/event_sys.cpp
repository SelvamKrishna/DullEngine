#include "engine/config.hpp"
#include "engine/core/event_sys.hpp"

namespace dull::core {

uint64_t EventBus::bind(std::string_view event_name, EventCallback callback) {
  static uint64_t s_next = 1;
  uint64_t id = s_next++;

  _listeners[std::string{event_name}].emplace_back(Listener{id, std::move(callback)});
  return id;
}

void EventBus::unbind(std::string_view event_name, uint64_t callback_id) {
  auto it = _listeners.find(event_name);
  if (it == _listeners.end()) return;

  std::erase_if(it->second, [&callback_id](const Listener& listener) {
    return listener.id == callback_id;
  });
}

void EventBus::emit(const Event& event) const noexcept {
  if (auto it = _listeners.find(event.getName()); it != _listeners.end()) {
    for (const auto& LISTENER : it->second) LISTENER.callback(event);
  }

  ZLOGI_IF(config::SHOULD_LOG_EVENT_SYS) << "Event emit : " << event.getName();
}


} // namespace dull::core
