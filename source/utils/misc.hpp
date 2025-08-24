#pragma once

#include <functional>
#include <string_view>

namespace Misc {
	struct TransparentStringHash {
		using is_transparent = void;
		
		size_t operator()(std::string_view sv) const noexcept {
			return std::hash<std::string_view>{}(sv);
		}
	};

	struct TransparentStringEqualTo {
		using is_transparent = void;
		
		bool operator()(std::string_view lhs, std::string_view rhs) const noexcept {
			return lhs == rhs;
		}
	};
}