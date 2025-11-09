#pragma once

#include <any>
#include <string>
#include <functional>
#include <unordered_map>

namespace dull::core {

struct Event {
private:
  std::string _name;
  std::unordered_map<std::string, std::any> _data;

public:
  Event() = delete;

  explicit Event(std::string name) noexcept : _name{std::move(name)} {}

  template <typename T>
  [[nodiscard]] T getData(const std::string& key) const { return std::any_cast<T>(_data.at(key)); }

  template <typename T>
  void setData(const std::string& key, T value) const { _data.at(key) = value; }

  [[nodiscard]] const std::string& getName() const noexcept { return _name; }
};

using EventCallback = std::function<void(const Event&)>;

class EventBus {
private:
  std::unordered_map<std::string, std::vector<EventCallback>> _listeners;

  explicit EventBus() = default;
  ~EventBus() = default;

  EventBus(const EventBus&) = default;
  EventBus(EventBus&&) = default;
  EventBus& operator=(const EventBus&) = default;
  EventBus& operator=(EventBus&&) = default;

public:
  void subscribe(const std::string& event_name, EventCallback callback) {
    _listeners[event_name].push_back(std::move(callback));
  }

  void emit(const Event& event) {
    if (auto it = _listeners.find(event.getName()); it != _listeners.end()) {
      for (auto& fn : it->second) fn(event);
    }
  }
};

} // namespace dull::core
