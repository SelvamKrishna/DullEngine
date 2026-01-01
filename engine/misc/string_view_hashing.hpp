#pragma once

#include <string_view>

namespace dull::misc {

// =======================
// Hasher for string with string_view key
// =======================
struct StringHash {
    using is_transparent = void;

    size_t operator()(std::string_view key) const noexcept
    {
        return std::hash<std::string_view>{}(key);
    }
};

// =======================
// Comparator b/w 2 string_view
// =======================
struct StringEq {
    using is_transparent = void;

    bool operator()(std::string_view lhs, std::string_view rhs) const noexcept
    {
        return lhs == rhs;
    }
};

} // namespace dull::misc
