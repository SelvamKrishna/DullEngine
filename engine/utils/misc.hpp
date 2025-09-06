#pragma once

#include <string_view>

namespace Misc {
	/// Structure to use string_view for string hashing
	struct TransparentStringHash {
		using is_transparent = void;
		
		size_t operator()(std::string_view sv) const noexcept {
			return std::hash<std::string_view>{}(sv);
		}
	};

	/// Structure to compare string_view for string hashing
	struct TransparentStringEqualTo {
		using is_transparent = void;
		
		bool operator()(std::string_view lhs, std::string_view rhs) const noexcept {
			return lhs == rhs;
		}
	};
}