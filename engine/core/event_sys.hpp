#pragma once

#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zutils/zutils.hpp>

#include <any>
#include <string>
#include <string_view>
#include <optional>
#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>

namespace dull::core {

struct Event final {
private:
  std::string _name;
  std::unordered_map<
    std::string,
    std::any,
    misc::StringHash,
    misc::StringEq
  > _data;

public:
  Event() = delete;
  explicit Event(std::string_view name) noexcept : _name{name} {}

  [[nodiscard]] std::string_view getName() const noexcept { return _name; }

  template <typename T>
  [[nodiscard]] T getData(std::string_view key) const {
    auto it = _data.find(key);
    ZASSERT(it != _data.end());
    return std::any_cast<T>(it->second);
  }

  template <typename T>
  [[nodiscard]] std::optional<T> tryGetData(std::string_view key) const noexcept {
    if (auto it = _data.find(key); it != _data.end()) {
      if (const T* VALUE = std::any_cast<T>(&it->second)) return *VALUE;
    }

    return std::nullopt;
  }

  template <typename T>
  void setData(std::string_view key, T&& value) { _data.emplace(key, std::forward<T>(value)); }
};

class EventBus final {
  friend class App;
  using EventCallback = std::function<void(const Event&)>;

private:
  struct Listener final {
    uint64_t id;
    EventCallback callback;
  };

  std::unordered_map<
    std::string,
    std::vector<Listener>,
    misc::StringHash,
    misc::StringEq
  > _listeners;

  explicit EventBus() = default;
  ~EventBus() = default;

public:
  uint64_t bind(std::string_view event_name, EventCallback callback);
  void unbind(std::string_view event_name, uint64_t callback_id);

  void emit(const Event& event) const noexcept;

  template <typename... KVPairs>
  void emit(std::string_view name, KVPairs&&... pairs) const {
    Event event {name};
    (event.setData(pairs.first, pairs.second), ...);
    emit(event);
  }
};

} // namespace dull::core
