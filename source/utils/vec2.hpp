#pragma once

#include <cmath>

#include "../../vendor/raylib.h"

struct Vec2 {
public:
  float x, y;

public:
  constexpr Vec2(float x = 0.0f, float y = 0.0f) noexcept : x(x), y(y) {}

  // Constructor from a raylib::Vector2
  constexpr operator Vector2() const noexcept { return {x, y}; }

  // Copy from raylib::Vector2 to Vec2
  constexpr Vec2(const Vector2 &vec) noexcept : x(vec.x), y(vec.y) {}

  inline static Vec2 unit(float unit = 0.0f) { return {unit, unit}; }

  constexpr Vec2 operator+(const Vec2 &other) const noexcept { return {x + other.x, y + other.y}; }
  constexpr Vec2 operator-(const Vec2 &other) const noexcept { return {x - other.x, y - other.y}; }
  constexpr Vec2 operator*(const Vec2 &other) const noexcept { return {x * other.x, y * other.y}; }
  constexpr Vec2 operator/(const Vec2 &other) const noexcept { return {x / other.x, y / other.y}; }
  constexpr Vec2 operator+(float scalar) const noexcept { return {x + scalar, y + scalar}; }
  constexpr Vec2 operator-(float scalar) const noexcept { return {x - scalar, y - scalar}; }
  constexpr Vec2 operator*(float scalar) const noexcept { return {x * scalar, y * scalar}; }
  constexpr Vec2 operator/(float scalar) const noexcept { return {x / scalar, y / scalar}; }

  Vec2 &operator+=(const Vec2 &other) noexcept {
    x += other.x;
    y += other.y;
    return *this;
  }

  Vec2 &operator-=(const Vec2 &other) noexcept {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  Vec2 &operator*=(const Vec2 &other) noexcept {
    x *= other.x;
    y *= other.y;
    return *this;
  }

  Vec2 &operator/=(const Vec2 &other) noexcept {
    x /= other.x;
    y /= other.y;
    return *this;
  }

  Vec2 &operator+=(float scalar) noexcept {
    x += scalar;
    y += scalar;
    return *this;
  }

  Vec2 &operator-=(float scalar) noexcept {
    x -= scalar;
    y -= scalar;
    return *this;
  }

  Vec2 &operator*=(float scalar) noexcept {
    x *= scalar;
    y *= scalar;
    return *this;
  }

  Vec2 &operator/=(float scalar) noexcept {
    x /= scalar;
    y /= scalar;
    return *this;
  }

  constexpr bool operator==(const Vec2 &other) const noexcept {
    return x == other.x && y == other.y;
  }

  constexpr bool operator!=(const Vec2 &other) const noexcept {
    return x != other.x || y != other.y;
  }

  constexpr Vec2 operator-() const noexcept { return {-x, -y}; }

  [[nodiscard]] float length() const noexcept { return std::sqrt(x * x + y * y); }

  [[nodiscard]] Vec2 normalized() const noexcept {
    float len = length();
    if (len == 0.0f) return Vec2::zero();
    return {x / len, y / len};
  }

  void normalize() noexcept {
    float len = length();
    if (len != 0.0f) {
      x /= len;
      y /= len;
    }
  }

  constexpr float dot(const Vec2 &other) const noexcept { return x * other.x + y * other.y; }
  constexpr float cross(const Vec2 &other) const noexcept { return x * other.y - y * other.x; }

  [[nodiscard]] float distance(const Vec2 &other) const noexcept {
    return (*this - other).length();
  }

  inline static constexpr Vec2 zero() noexcept { return {0.f, 0.f}; }
  inline static constexpr Vec2 one() noexcept { return {1.f, 1.f}; }
  inline static constexpr Vec2 up() noexcept { return {0.f, 1.f}; }
  inline static constexpr Vec2 down() noexcept { return {0.f, -1.f}; }
  inline static constexpr Vec2 left() noexcept { return {-1.f, 0.f}; }
  inline static constexpr Vec2 right() noexcept { return {1.f, 0.f}; }
};