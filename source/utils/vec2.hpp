#pragma once

#include "../../vendor/raylib.h"
#include <cmath>
#include <cstdint>

struct Vec2 {
    float x, y;

    constexpr Vec2(float x = 0.0F, float y = 0.0F) noexcept : x(x), y(y) {}

    // From raylib::Vector2
    constexpr Vec2(const Vector2 &vec) noexcept : x(vec.x), y(vec.y) {}

    // To raylib::Vector2
    constexpr operator Vector2() const noexcept { return {x, y}; }

    static Vec2 unit(float unit = 0.0F) { return {unit, unit}; }

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

    constexpr bool operator==(const Vec2 &other) const noexcept { return x == other.x && y == other.y; }
    constexpr bool operator!=(const Vec2 &other) const noexcept { return !(*this == other); }
    constexpr Vec2 operator-() const noexcept { return {-x, -y}; }

    static Vec2 from_angle(float radians) noexcept { return {std::cos(radians), std::sin(radians)}; }

    [[nodiscard]] float length() const noexcept { return std::hypot(x, y); }
    [[nodiscard]] float length_squared() const noexcept { return (x * x) + (y * y); }

    [[nodiscard]] Vec2 normalized() const noexcept {
        const float LEN = length();
        return LEN > 0.0F ? *this / LEN : zero();
    }

    void normalize() noexcept {
        const float LEN = length();
        if (LEN > 0.0F) {
            x /= LEN;
            y /= LEN;
        }
    }

    [[nodiscard]] constexpr float dot(const Vec2 &other) const noexcept {
        return (x * other.x) + (y * other.y);
    }

    [[nodiscard]] constexpr float cross(const Vec2 &other) const noexcept {
        return (x * other.y) - (y * other.x);
    }

    [[nodiscard]] float distance(const Vec2 &other) const noexcept { return (*this - other).length(); }

    static constexpr Vec2 zero() noexcept { return {}; }
    static constexpr Vec2 one() noexcept { return {1.0F, 1.0F}; }
    static constexpr Vec2 up() noexcept { return {0.0F, 1.0F}; }
    static constexpr Vec2 down() noexcept { return {0.0F, -1.0F}; }
    static constexpr Vec2 left() noexcept { return {-1.0F, 0.0F}; }
    static constexpr Vec2 right() noexcept { return {1.0F, 0.0F}; }
};

constexpr Vec2 operator+(float scalar, const Vec2 &vec) noexcept { return vec + scalar; }
constexpr Vec2 operator*(float scalar, const Vec2 &vec) noexcept { return vec * scalar; }

struct Vec2i {
    int32_t x, y;

    constexpr Vec2i(int32_t x = 0, int32_t y = 0) noexcept : x(x), y(y) {}

    // From raylib::Vector2 (float to int32_t)
    constexpr Vec2i(const Vector2 &vec) noexcept
        : x(static_cast<int32_t>(vec.x)), y(static_cast<int32_t>(vec.y)) {}

    // To raylib::Vector2 (int32_t to float)
    constexpr operator Vector2() const noexcept { return {static_cast<float>(x), static_cast<float>(y)}; }

    static Vec2i unit(int32_t unit = 0) { return {unit, unit}; }

    constexpr Vec2i operator+(const Vec2i &other) const noexcept { return {x + other.x, y + other.y}; }
    constexpr Vec2i operator-(const Vec2i &other) const noexcept { return {x - other.x, y - other.y}; }
    constexpr Vec2i operator*(const Vec2i &other) const noexcept { return {x * other.x, y * other.y}; }
    constexpr Vec2i operator/(const Vec2i &other) const noexcept { return {x / other.x, y / other.y}; }

    constexpr Vec2i operator+(int32_t scalar) const noexcept { return {x + scalar, y + scalar}; }
    constexpr Vec2i operator-(int32_t scalar) const noexcept { return {x - scalar, y - scalar}; }
    constexpr Vec2i operator*(int32_t scalar) const noexcept { return {x * scalar, y * scalar}; }
    constexpr Vec2i operator/(int32_t scalar) const noexcept { return {x / scalar, y / scalar}; }

    Vec2i &operator+=(const Vec2i &other) noexcept {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vec2i &operator-=(const Vec2i &other) noexcept {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vec2i &operator*=(const Vec2i &other) noexcept {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vec2i &operator/=(const Vec2i &other) noexcept {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vec2i &operator+=(int32_t scalar) noexcept {
        x += scalar;
        y += scalar;
        return *this;
    }
    Vec2i &operator-=(int32_t scalar) noexcept {
        x -= scalar;
        y -= scalar;
        return *this;
    }
    Vec2i &operator*=(int32_t scalar) noexcept {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Vec2i &operator/=(int32_t scalar) noexcept {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr bool operator==(const Vec2i &other) const noexcept { return x == other.x && y == other.y; }
    constexpr bool operator!=(const Vec2i &other) const noexcept { return !(*this == other); }
    constexpr Vec2i operator-() const noexcept { return {-x, -y}; }

    static Vec2i from_angle(float radians) noexcept {
        return {static_cast<int32_t>(std::cos(radians)), static_cast<int32_t>(std::sin(radians))};
    }

    [[nodiscard]] float length() const noexcept {
        return std::hypot(static_cast<float>(x), static_cast<float>(y));
    }
    [[nodiscard]] int32_t length_squared() const noexcept { return (x * x) + (y * y); }

    [[nodiscard]] Vec2i normalized() const noexcept {
        const float LEN = length();
        return LEN > 0.0F ? *this / static_cast<int32_t>(LEN) : zero();
    }

    void normalize() noexcept {
        const float LEN = length();
        if (LEN > 0.0F) {
            x = static_cast<int32_t>(static_cast<float>(x) / LEN);
            y = static_cast<int32_t>(static_cast<float>(y) / LEN);
        }
    }

    [[nodiscard]] constexpr int32_t dot(const Vec2i &other) const noexcept {
        return (x * other.x) + (y * other.y);
    }

    [[nodiscard]] constexpr int32_t cross(const Vec2i &other) const noexcept {
        return (x * other.y) - (y * other.x);
    }

    [[nodiscard]] float distance(const Vec2i &other) const noexcept { return (*this - other).length(); }

    static constexpr Vec2i zero() noexcept { return {}; }
    static constexpr Vec2i one() noexcept { return {1, 1}; }
    static constexpr Vec2i up() noexcept { return {0, 1}; }
    static constexpr Vec2i down() noexcept { return {0, -1}; }
    static constexpr Vec2i left() noexcept { return {-1, 0}; }
    static constexpr Vec2i right() noexcept { return {1, 0}; }
};

constexpr Vec2i operator+(int32_t scalar, const Vec2i &vec) noexcept { return vec + scalar; }
constexpr Vec2i operator*(int32_t scalar, const Vec2i &vec) noexcept { return vec * scalar; }
