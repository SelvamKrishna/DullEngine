#pragma once

#include "vendor/raylib.h"

#include <cstdint>

struct color {
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;

	constexpr color() noexcept : r(0), g(0), b(0), a(255) {}
	constexpr color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
	: r(r)
	, g(g)
	, b(b)
	, a(a) {}

	// From raylib::Color
	constexpr color(const Color& color) noexcept
	: r(color.r)
	, g(color.g)
	, b(color.b)
	, a(color.a) {}

	// To raylib::Color
	constexpr operator Color() const noexcept { return {r, g, b, a}; }

	constexpr color operator+(const color& other) const noexcept {
		return {
			static_cast<uint8_t>(r + other.r),
			static_cast<uint8_t>(g + other.g),
			static_cast<uint8_t>(b + other.b),
			static_cast<uint8_t>(a + other.a)
		};
	}

	constexpr color operator-(const color& other) const noexcept {
		return {
			static_cast<uint8_t>(r - other.r),
			static_cast<uint8_t>(g - other.g),
			static_cast<uint8_t>(b - other.b),
			static_cast<uint8_t>(a - other.a)
		};
	}

	constexpr color operator*(const color& other) const noexcept {
		return {
			static_cast<uint8_t>(r * other.r / 255),
			static_cast<uint8_t>(g * other.g / 255),
			static_cast<uint8_t>(b * other.b / 255),
			static_cast<uint8_t>(a * other.a / 255)
		};
	}

	constexpr color operator/(const color& other) const noexcept {
		return {
			static_cast<uint8_t>(r / other.r),
			static_cast<uint8_t>(g / other.g),
			static_cast<uint8_t>(b / other.b),
			static_cast<uint8_t>(a / other.a)
		};
	}

	constexpr color operator+(uint8_t scalar) const noexcept {
		return {
			static_cast<uint8_t>(r + scalar),
			static_cast<uint8_t>(g + scalar),
			static_cast<uint8_t>(b + scalar),
			static_cast<uint8_t>(a + scalar)
		};
	}

	constexpr color operator-(uint8_t scalar) const noexcept {
		return {
			static_cast<uint8_t>(r - scalar),
			static_cast<uint8_t>(g - scalar),
			static_cast<uint8_t>(b - scalar),
			static_cast<uint8_t>(a - scalar)
		};
	}

	constexpr color operator*(uint8_t scalar) const noexcept {
		return {
			static_cast<uint8_t>(r * scalar / 255),
			static_cast<uint8_t>(g * scalar / 255),
			static_cast<uint8_t>(b * scalar / 255),
			static_cast<uint8_t>(a * scalar / 255)
		};
	}

	constexpr color operator/(uint8_t scalar) const noexcept {
		return {
			static_cast<uint8_t>(r / scalar),
			static_cast<uint8_t>(g / scalar),
			static_cast<uint8_t>(b / scalar),
			static_cast<uint8_t>(a / scalar)
		};
	}

	constexpr color& operator+=(const color& other) noexcept {
		r += other.r;
		g += other.g;
		b += other.b;
		a += other.a;
		return *this;
	}

	constexpr color& operator-=(const color& other) noexcept {
		r -= other.r;
		g -= other.g;
		b -= other.b;
		a -= other.a;
		return *this;
	}

	constexpr color& operator*=(const color& other) noexcept {
		r = static_cast<uint8_t>(r * other.r / 255);
		g = static_cast<uint8_t>(g * other.g / 255);
		b = static_cast<uint8_t>(b * other.b / 255);
		a = static_cast<uint8_t>(a * other.a / 255);
		return *this;
	}

	constexpr color& operator/=(const color& other) noexcept {
		r = static_cast<uint8_t>(r / other.r);
		g = static_cast<uint8_t>(g / other.g);
		b = static_cast<uint8_t>(b / other.b);
		a = static_cast<uint8_t>(a / other.a);
		return *this;
	}

	constexpr color& operator+=(uint8_t scalar) noexcept {
		r += scalar;
		g += scalar;
		b += scalar;
		a += scalar;
		return *this;
	}

	constexpr color& operator-=(uint8_t scalar) noexcept {
		r -= scalar;
		g -= scalar;
		b -= scalar;
		a -= scalar;
		return *this;
	}

	constexpr color& operator*=(uint8_t scalar) noexcept {
		r = static_cast<uint8_t>(r * scalar / 255);
		g = static_cast<uint8_t>(g * scalar / 255);
		b = static_cast<uint8_t>(b * scalar / 255);
		a = static_cast<uint8_t>(a * scalar / 255);
		return *this;
	}

	constexpr color& operator/=(uint8_t scalar) noexcept {
		r = static_cast<uint8_t>(r / scalar);
		g = static_cast<uint8_t>(g / scalar);
		b = static_cast<uint8_t>(b / scalar);
		a = static_cast<uint8_t>(a / scalar);
		return *this;
	}

	constexpr bool operator==(const color& other) const noexcept {
		return r == other.r && g == other.g && b == other.b && a == other.a;
	}

	constexpr bool operator!=(const color& other) const noexcept {
		return r != other.r || g != other.g || b != other.b || a != other.a;
	}

	static constexpr color fromHex(uint32_t hex) noexcept {
		return {
			static_cast<uint8_t>((hex >> 16) & 0xFF),
			static_cast<uint8_t>((hex >>  8) & 0xFF),
			static_cast<uint8_t>( hex        & 0xFF),
			static_cast<uint8_t>((hex >> 24) & 0xFF)
		};
	}

	[[nodiscard]] constexpr uint32_t toHex() const noexcept {
		return \
			static_cast<uint32_t>(r) << 16 | 
			static_cast<uint32_t>(g) << 8 | 
			static_cast<uint32_t>(b) | 
			static_cast<uint32_t>(a) << 24;
	}

	[[nodiscard]] constexpr color inverted() const noexcept {
		return {
			static_cast<uint8_t>(UINT8_MAX - r),
			static_cast<uint8_t>(UINT8_MAX - g),
			static_cast<uint8_t>(UINT8_MAX - b),
			a
		};
	}

	[[nodiscard]] constexpr color grayscale() const noexcept {
		constexpr float LUMINOSITY_R { 0.3F };
		constexpr float LUMINOSITY_G { 0.59F };
		constexpr float LUMINOSITY_B { 0.11F };

		float weighted_luminosity { 0.0F };

		weighted_luminosity += static_cast<float>(r) * LUMINOSITY_R;
		weighted_luminosity += static_cast<float>(g) * LUMINOSITY_G;
		weighted_luminosity += static_cast<float>(b) * LUMINOSITY_B;

		const auto GRAYSCALED { static_cast<uint8_t>(weighted_luminosity) };

		return {GRAYSCALED, GRAYSCALED, GRAYSCALED, a};
	}

	static constexpr color white() noexcept   { return {255, 255, 255}; }
	static constexpr color black() noexcept   { return {0,   0,   0  }; }
	static constexpr color red() noexcept     { return {255, 0,   0  }; }
	static constexpr color green() noexcept   { return {0,   255, 0  }; }
	static constexpr color blue() noexcept    { return {0,   0,   255}; }
	static constexpr color yellow() noexcept  { return {255, 255, 0  }; }
	static constexpr color cyan() noexcept    { return {0,   255, 255}; }
	static constexpr color magenta() noexcept { return {255, 0,   255}; }

	static constexpr color transparent() noexcept { return {0, 0, 0, 0}; }
};