#pragma once

#include "engine/misc/string_view_hashing.hpp"

#include <any>
#include <string>
#include <string_view>
#include <optional>
#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>

namespace dull::core {

struct Event {
private:
  std::string _name;
  std::unordered_map<
    std::string,
    std::any,
    misc::StringHash,
    misc::StringEq
  > _data;

public:
  void* sender = nullptr;

  Event() = delete;
  explicit Event(std::string_view name) noexcept : _name{name} {}

  [[nodiscard]] std::string_view getName() const noexcept { return _name; }

  template <typename T>
  [[nodiscard]] T getData(std::string_view key) const {
    auto it = _data.find(key);
    return std::any_cast<T>(it->second);
  }

  template <typename T>
  [[nodiscard]] std::optional<T> tryGetData(std::string_view key) const noexcept {
    if (auto it = _data.find(key); it != _data.end()) {
      if (auto val = std::any_cast<T>(&it->second)) return *val;
    }

    return std::nullopt;
  }

  template <typename T>
  void setData(std::string_view key, T&& value) { _data[std::string{key}] = std::forward<T>(value); }
};

using EventCallback = std::function<void(const Event&)>;

class EventBus {
private:
  std::unordered_map<
    std::string,
    std::vector<EventCallback>,
    misc::StringHash,
    misc::StringEq
  > _listeners;

  explicit EventBus() = default;
  ~EventBus() = default;

  friend class App;

public:
  void subscribe(std::string_view event_name, EventCallback callback) {
    if (auto it = _listeners.find(event_name); it != _listeners.end())
      it->second.push_back(std::move(callback));
    else
      _listeners.emplace(std::string(event_name), std::vector<EventCallback>{std::move(callback)});
  }

  void emit(const Event& event) const noexcept {
    if (auto it = _listeners.find(std::string(event.getName())); it != _listeners.end()) {
      for (const auto& FN : it->second) FN(event);
    }
  }

  template <typename... Args>
  void emit(std::string_view name, Args&&... args) const {
    Event e {name};
    (e.setData(std::forward<Args>(args).first, std::forward<Args>(args).second), ...);
    emit(e);
  }
};

} // namespace dull::core
