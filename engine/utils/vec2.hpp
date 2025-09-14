#pragma once

#include "vendor/raylib.h"

#include <cmath>
#include <cstdint>

struct vec2 {
public:
	float x, y;

	constexpr vec2(float x = 0.0F, float y = 0.0F) noexcept : x(x), y(y) {}
	constexpr vec2(const Vector2& vec) noexcept : x(vec.x), y(vec.y) {}
	constexpr operator Vector2() const noexcept { return {x, y}; }

	static constexpr vec2 unit(float unit = 0.0F) { return {unit, unit}; }

	constexpr vec2 operator+(const vec2& other) const noexcept { return {x + other.x, y + other.y}; }
	constexpr vec2 operator-(const vec2& other) const noexcept { return {x - other.x, y - other.y}; }
	constexpr vec2 operator*(const vec2& other) const noexcept { return {x * other.x, y * other.y}; }
	constexpr vec2 operator/(const vec2& other) const noexcept { return {x / other.x, y / other.y}; }

	constexpr vec2 operator+(float scalar) const noexcept { return {x + scalar, y + scalar}; }
	constexpr vec2 operator-(float scalar) const noexcept { return {x - scalar, y - scalar}; }
	constexpr vec2 operator*(float scalar) const noexcept { return {x * scalar, y * scalar}; }
	constexpr vec2 operator/(float scalar) const noexcept { return {x / scalar, y / scalar}; }

	vec2& operator+=(const vec2& other) noexcept { x += other.x; y += other.y; return *this; }
	vec2& operator-=(const vec2& other) noexcept { x -= other.x; y -= other.y; return *this; }
	vec2& operator*=(const vec2& other) noexcept { x *= other.x; y *= other.y; return *this; }
	vec2& operator/=(const vec2& other) noexcept { x /= other.x; y /= other.y; return *this; }

	vec2& operator+=(float scalar) noexcept { x += scalar; y += scalar; return *this; }
	vec2& operator-=(float scalar) noexcept { x -= scalar; y -= scalar; return *this; }
	vec2& operator*=(float scalar) noexcept { x *= scalar; y *= scalar; return *this; }
	vec2& operator/=(float scalar) noexcept { x /= scalar; y /= scalar; return *this; }

	constexpr bool operator==(const vec2& other) const noexcept { return x == other.x && y == other.y; }
	constexpr bool operator!=(const vec2& other) const noexcept { return !(*this == other); }
	constexpr vec2 operator-() const noexcept { return {-x, -y}; }

	static vec2 from_angle(float rad) noexcept { return {std::cos(rad), std::sin(rad)}; }

	[[nodiscard]] float length() const noexcept { return std::hypot(x, y); }
	[[nodiscard]] float length_squared() const noexcept { return x * x + y * y; }

	[[nodiscard]] vec2 normalized() const noexcept {
		const float LEN { length() };
		return LEN > 0.0F ? *this / LEN : zero();
	}

	void normalize() noexcept {
		const float LEN { length() };
		if (LEN > 0.0F) { x /= LEN; y /= LEN; }
	}

	[[nodiscard]] constexpr float dot(const vec2& other) const noexcept { return x * other.x + y * other.y; }
	[[nodiscard]] constexpr float cross(const vec2& other) const noexcept { return x * other.y - y * other.x; }
	[[nodiscard]] float distance(const vec2& other) const noexcept { return (*this - other).length(); }

	static constexpr vec2 zero() noexcept { return {}; }
	static constexpr vec2 one() noexcept { return {1.0F, 1.0F}; }
	static constexpr vec2 up() noexcept { return {0.0F, 1.0F}; }
	static constexpr vec2 down() noexcept { return {0.0F, -1.0F}; }
	static constexpr vec2 left() noexcept { return {-1.0F, 0.0F}; }
	static constexpr vec2 right() noexcept { return {1.0F, 0.0F}; }
};

constexpr vec2 operator+(float scalar, const vec2& vec) noexcept { return vec + scalar; }
constexpr vec2 operator*(float scalar, const vec2& vec) noexcept { return vec * scalar; }

struct vec2i {
public:
	int32_t x, y;

	constexpr vec2i(int32_t x = 0, int32_t y = 0) noexcept : x(x), y(y) {}
	constexpr vec2i(const Vector2& vec) noexcept : x(static_cast<int32_t>(vec.x)), y(static_cast<int32_t>(vec.y)) {}
	constexpr operator Vector2() const noexcept { return {static_cast<float>(x), static_cast<float>(y)}; }

	static vec2i unit(int32_t unit = 0) { return {unit, unit}; }

	constexpr vec2i operator+(const vec2i& other) const noexcept { return {x + other.x, y + other.y}; }
	constexpr vec2i operator-(const vec2i& other) const noexcept { return {x - other.x, y - other.y}; }
	constexpr vec2i operator*(const vec2i& other) const noexcept { return {x * other.x, y * other.y}; }
	constexpr vec2i operator/(const vec2i& other) const noexcept { return {x / other.x, y / other.y}; }

	constexpr vec2i operator+(int32_t scalar) const noexcept { return {x + scalar, y + scalar}; }
	constexpr vec2i operator-(int32_t scalar) const noexcept { return {x - scalar, y - scalar}; }
	constexpr vec2i operator*(int32_t scalar) const noexcept { return {x * scalar, y * scalar}; }
	constexpr vec2i operator/(int32_t scalar) const noexcept { return {x / scalar, y / scalar}; }

	vec2i& operator+=(const vec2i& other) noexcept { x += other.x; y += other.y; return *this; }
	vec2i& operator-=(const vec2i& other) noexcept { x -= other.x; y -= other.y; return *this; }
	vec2i& operator*=(const vec2i& other) noexcept { x *= other.x; y *= other.y; return *this; }
	vec2i& operator/=(const vec2i& other) noexcept { x /= other.x; y /= other.y; return *this; }

	vec2i& operator+=(int32_t scalar) noexcept { x += scalar; y += scalar; return *this; }
	vec2i& operator-=(int32_t scalar) noexcept { x -= scalar; y -= scalar; return *this; }
	vec2i& operator*=(int32_t scalar) noexcept { x *= scalar; y *= scalar; return *this; }
	vec2i& operator/=(int32_t scalar) noexcept { x /= scalar; y /= scalar; return *this; }

	constexpr bool operator==(const vec2i& other) const noexcept { return x == other.x && y == other.y; }
	constexpr bool operator!=(const vec2i& other) const noexcept { return !(*this == other); }
	constexpr vec2i operator-() const noexcept { return {-x, -y}; }

	static vec2i from_angle(float rad) noexcept { return {static_cast<int32_t>(std::cos(rad)), static_cast<int32_t>(std::sin(rad))}; }

	[[nodiscard]] float length() const noexcept { return std::hypot(static_cast<float>(x), static_cast<float>(y)); }
	[[nodiscard]] int32_t length_squared() const noexcept { return x * x + y * y; }

	[[nodiscard]] vec2i normalized() const noexcept {
		const float LEN { length() };
		return LEN > 0.0F ? *this / static_cast<int32_t>(LEN) : zero();
	}

	void normalize() noexcept {
		const float LEN { length() };
		if (LEN > 0.0F) { x = static_cast<int32_t>(x / LEN); y = static_cast<int32_t>(y / LEN); }
	}

	[[nodiscard]] constexpr int32_t dot(const vec2i& other) const noexcept { return x * other.x + y * other.y; }
	[[nodiscard]] constexpr int32_t cross(const vec2i& other) const noexcept { return x * other.y - y * other.x; }
	[[nodiscard]] float distance(const vec2i& other) const noexcept { return (*this - other).length(); }

	static constexpr vec2i zero() noexcept { return {}; }
	static constexpr vec2i one() noexcept { return {1, 1}; }
	static constexpr vec2i up() noexcept { return {0, 1}; }
	static constexpr vec2i down() noexcept { return {0, -1}; }
	static constexpr vec2i left() noexcept { return {-1, 0}; }
	static constexpr vec2i right() noexcept { return {1, 0}; }
};

constexpr vec2i operator+(int32_t scalar, const vec2i &vec) noexcept { return vec + scalar; }