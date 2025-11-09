#pragma once

#include <string>
#include <unordered_map>
#include <any>

namespace dull::core {

enum class EventCategory : uint8_t {
  None,
  Input,
  Window,
  Custom,
};

struct Event {
private:
  std::string _name;
  EventCategory _category {EventCategory::Custom};
  std::unordered_map<std::string, std::any> _data;

public:
  Event() = delete;

  explicit Event(std::string name) noexcept : _name{std::move(name)} {}

  explicit Event(std::string name, EventCategory category) noexcept
  : _name{std::move(name)}, _category{category} {}

  template <typename T>
  [[nodiscard]] T getData(const std::string& key) const { return std::any_cast<T>(_data.at(key)); }

  template <typename T>
  void setData(const std::string& key, T value) const { _data.at(key) = value; }
};

} // namespace dull::core
