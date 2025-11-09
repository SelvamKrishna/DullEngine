#pragma once

#include <string_view>

namespace dull::misc {

struct StringHash {
  using is_transparent = void;

  size_t operator()(std::string_view s) const noexcept {
    return std::hash<std::string_view>{}(s);
  }
};

struct StringEq {
  using is_transparent = void;

  bool operator()(std::string_view a, std::string_view b) const noexcept {
    return a == b;
  }
};

} // namespace dull::misc
