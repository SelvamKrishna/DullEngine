#pragma once

#include <vendor/raylib.h>

#include <cstdint>

namespace dull::util {

struct ColorRGBA {
	uint8_t r {0};
	uint8_t g {0};
	uint8_t b {0};
	uint8_t a {255};

/// --- Constructors ---

	constexpr ColorRGBA() noexcept = default;

	constexpr ColorRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
  : r{r}, g{g}, b{b}, a{a} {}

	constexpr ColorRGBA(const Color& rl_color) noexcept
  : r{rl_color.r}, g{rl_color.g}, b{rl_color.b}, a{rl_color.a} {}

/// --- Pre-defined Colors ---

  #define FACTORY(NAME, RR, GG, BB, AA) \
    [[nodiscard]] static constexpr ColorRGBA NAME() noexcept { return {RR, GG, BB, AA}; }

	FACTORY(kTransparent, 0, 0, 0, 0)

	FACTORY(kWhite  , 255, 255, 255, 255)
	FACTORY(kBlack  , 0  , 0  , 0  , 255)
	FACTORY(kRed    , 255, 0  , 0  , 255)
	FACTORY(kGreen  , 0  , 255, 0  , 255)
	FACTORY(kBlue   , 0  , 0  , 255, 255)
	FACTORY(kYellow , 255, 255, 0  , 255)
	FACTORY(kCyan   , 0  , 255, 255, 255)
	FACTORY(kMagenta, 255, 0  , 255, 255)

  #undef FACTORY

/// --- Hex conversions ---

	[[nodiscard]] static constexpr ColorRGBA fromHex(uint32_t hex) noexcept {
		return (hex <= 0xFFFFFF)
    ? ColorRGBA{ /// RR, GG, BB with max Alpha
      static_cast<uint8_t>((hex >> 16) & 0xFF),
      static_cast<uint8_t>((hex >>  8) & 0xFF),
      static_cast<uint8_t>( hex        & 0xFF),
      255
    }
    : ColorRGBA{ /// RR, GG, BB, AA
      static_cast<uint8_t>((hex >> 24) & 0xFF),
      static_cast<uint8_t>((hex >> 16) & 0xFF),
      static_cast<uint8_t>((hex >>  8) & 0xFF),
      static_cast<uint8_t>( hex        & 0xFF)
    };
	}

	[[nodiscard]] constexpr uint32_t toHex() const noexcept {
		return \
      (static_cast<uint32_t>(a) << 24) |
      (static_cast<uint32_t>(r) << 16) |
      (static_cast<uint32_t>(g) << 8)  |
      (static_cast<uint32_t>(b) << 0);
	}

// --- Color utilities ---

	[[nodiscard]] constexpr ColorRGBA inverted() const noexcept {
		return {
      static_cast<uint8_t>(255 - r),
      static_cast<uint8_t>(255 - g),
      static_cast<uint8_t>(255 - b),
      a
    };
	}

	[[nodiscard]] constexpr ColorRGBA grayscaled() const noexcept {
		constexpr float L_R = 0.3F;
		constexpr float L_G = 0.59F;
		constexpr float L_B = 0.11F;

		const uint8_t GRAYSCALE = static_cast<uint8_t>(r * L_R + g * L_G + b * L_B);
		return {GRAYSCALE, GRAYSCALE, GRAYSCALE, a};
	}

/// --- Operators (Color <op> Color) ---

	constexpr ColorRGBA operator+(const ColorRGBA& other) const noexcept {
		return {
      static_cast<uint8_t>(r + other.r),
			static_cast<uint8_t>(g + other.g),
			static_cast<uint8_t>(b + other.b),
			static_cast<uint8_t>(a + other.a)
    };
	}

	constexpr ColorRGBA operator-(const ColorRGBA& other) const noexcept {
		return {
      static_cast<uint8_t>(r - other.r),
			static_cast<uint8_t>(g - other.g),
			static_cast<uint8_t>(b - other.b),
			static_cast<uint8_t>(a - other.a)
    };
	}

	constexpr ColorRGBA operator*(const ColorRGBA& other) const noexcept {
		return {
      static_cast<uint8_t>(r * other.r / 255),
			static_cast<uint8_t>(g * other.g / 255),
			static_cast<uint8_t>(b * other.b / 255),
			static_cast<uint8_t>(a * other.a / 255)
    };
	}

	constexpr ColorRGBA operator/(const ColorRGBA& other) const noexcept {
		return {
      static_cast<uint8_t>(other.r ? r / other.r : 255),
      static_cast<uint8_t>(other.g ? g / other.g : 255),
      static_cast<uint8_t>(other.b ? b / other.b : 255),
      static_cast<uint8_t>(other.a ? a / other.a : 255)
    };
	}

	constexpr ColorRGBA& operator+=(const ColorRGBA& other) noexcept { return *this = *this + other; }
	constexpr ColorRGBA& operator-=(const ColorRGBA& other) noexcept { return *this = *this - other; }
	constexpr ColorRGBA& operator*=(const ColorRGBA& other) noexcept { return *this = *this * other; }
	constexpr ColorRGBA& operator/=(const ColorRGBA& other) noexcept { return *this = *this / other; }

/// --- Operators (Color <op> scalar) ---

	constexpr ColorRGBA operator+(uint8_t scalar) const noexcept { return *this + ColorRGBA{scalar, scalar, scalar, 255}; }
	constexpr ColorRGBA operator-(uint8_t scalar) const noexcept { return *this - ColorRGBA{scalar, scalar, scalar, 255}; }
	constexpr ColorRGBA operator*(uint8_t scalar) const noexcept { return *this * ColorRGBA{scalar, scalar, scalar, 255}; }
	constexpr ColorRGBA operator/(uint8_t scalar) const noexcept { return *this / ColorRGBA{scalar, scalar, scalar, 255}; }

	constexpr ColorRGBA& operator+=(uint8_t scalar) noexcept { return *this = *this + scalar; }
	constexpr ColorRGBA& operator-=(uint8_t scalar) noexcept { return *this = *this - scalar; }
	constexpr ColorRGBA& operator*=(uint8_t scalar) noexcept { return *this = *this * scalar; }
	constexpr ColorRGBA& operator/=(uint8_t scalar) noexcept { return *this = *this / scalar; }

/// --- Comparison ---

	constexpr bool operator==(const ColorRGBA& other) const noexcept = default;
	constexpr bool operator!=(const ColorRGBA& other) const noexcept = default;

/// --- Conversion ---

	constexpr operator Color() const noexcept { return {r, g, b, a}; }

};

} // namespace dull::util