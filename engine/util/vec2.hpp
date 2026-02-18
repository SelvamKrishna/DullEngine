#pragma once

#include <vendor/raylib.h>

#include <cmath>
#include <type_traits>

namespace dull::util {

// ---
// Data representation of a 2D vector
// ---
template <typename ValueT>
    requires std::is_arithmetic_v<ValueT>
struct Vec2 {
public:
    ValueT x, y;

// --- Constructors ---

    constexpr Vec2() noexcept = default;

    constexpr Vec2(ValueT x, ValueT y) noexcept : x{x}, y{y} {}

    constexpr Vec2(const rl::Vector2& rlVec) noexcept
        : x{static_cast<ValueT>(rlVec.x)}, y{static_cast<ValueT>(rlVec.y)}
    {}

    [[nodiscard]] static constexpr Vec2 Zero () noexcept { return { 0,  0 }; }
    [[nodiscard]] static constexpr Vec2 One  () noexcept { return { 1,  1 }; }
    [[nodiscard]] static constexpr Vec2 Up   () noexcept { return { 0,  1 }; }
    [[nodiscard]] static constexpr Vec2 Down () noexcept { return { 0, -1 }; }
    [[nodiscard]] static constexpr Vec2 Left () noexcept { return {-1,  0 }; }
    [[nodiscard]] static constexpr Vec2 Right() noexcept { return { 1,  0 }; }

    static constexpr Vec2 Unit(ValueT val = 1) noexcept { return {val, val}; }

// --- Vector math ---

    [[nodiscard]] constexpr ValueT Dot(const Vec2& other) const noexcept
    {
        return this->x * other.x + this->y * other.y;
    }

    [[nodiscard]] constexpr ValueT Cross(const Vec2& other) const noexcept
    {
        return this->x * other.y - this->y * other.x;
    }

    [[nodiscard]] constexpr Vec2 Perpendicular() const noexcept { return {-this->y, this->x}; }
    [[nodiscard]] ValueT Length() const noexcept { return std::hypot(this->x, this->y); }
    [[nodiscard]] ValueT Distance(const Vec2& other) const noexcept { return (*this - other).Length(); }

    [[nodiscard]] Vec2 Normalized() const noexcept
    {
        const ValueT CURRENT_LENGTH = this->Length();
        return CURRENT_LENGTH ? (*this / CURRENT_LENGTH) : Vec2::Zero();
    }

    void Normalize() noexcept { *this = this->Normalized(); }

    [[nodiscard]] bool NearlyEquals(const Vec2& other, ValueT epsilon = static_cast<ValueT>(1e-6)) const noexcept
    {
        if constexpr (!std::is_floating_point_v<ValueT>)
            return this->x == other.x && this->y == other.y;

        return std::fabs(this->x - other.x) < epsilon && std::fabs(this->y - other.y) < epsilon;
    }

// --- Operators ---

    constexpr Vec2 operator - () const noexcept { return {-x, -y}; }

// -> Vector (op) Vector

    constexpr Vec2 operator + (const Vec2& other) const noexcept
    {
        return {this->x + other.x, this->y + other.y};
    }

    constexpr Vec2 operator - (const Vec2& other) const noexcept
    {
        return {this->x - other.x, this->y - other.y};
    }

    constexpr Vec2 operator * (const Vec2& other) const noexcept
    {
        return {this->x * other.x, this->y * other.y};
    }

    constexpr Vec2 operator / (const Vec2& other) const noexcept
    {
        return {this->x / other.x, this->y / other.y};
    }

    constexpr Vec2& operator += (const Vec2& other) const noexcept { return *this = *this + other; }
    constexpr Vec2& operator -= (const Vec2& other) const noexcept { return *this = *this - other; }
    constexpr Vec2& operator *= (const Vec2& other) const noexcept { return *this = *this * other; }
    constexpr Vec2& operator /= (const Vec2& other) const noexcept { return *this = *this / other; }

// -> Vector (op) Scalar

    constexpr Vec2 operator + (ValueT scalar) const noexcept { return {this->x + scalar, this->y + scalar}; }
    constexpr Vec2 operator - (ValueT scalar) const noexcept { return {this->x - scalar, this->y - scalar}; }
    constexpr Vec2 operator * (ValueT scalar) const noexcept { return {this->x * scalar, this->y * scalar}; }
    constexpr Vec2 operator / (ValueT scalar) const noexcept { return {this->x / scalar, this->y / scalar}; }

    constexpr Vec2& operator += (ValueT scalar) noexcept { this->x += scalar; this->y += scalar; return *this; }
    constexpr Vec2& operator -= (ValueT scalar) noexcept { this->x -= scalar; this->y -= scalar; return *this; }
    constexpr Vec2& operator *= (ValueT scalar) noexcept { this->x *= scalar; this->y *= scalar; return *this; }
    constexpr Vec2& operator /= (ValueT scalar) noexcept { this->x /= scalar; this->y /= scalar; return *this; }

// -> Comparison

    constexpr bool operator == (const Vec2& other) const noexcept = default;
    constexpr bool operator != (const Vec2& other) const noexcept = default;

// --- Conversion --

    [[nodiscard]] constexpr operator rl::Vector2() const noexcept
    {
        return {static_cast<float>(this->x), static_cast<float>(this->y)};
    }
};

template <typename T>
constexpr Vec2<T> operator + (T scalar, const Vec2<T>& vector) noexcept { return vector + scalar; }

template <typename T>
constexpr Vec2<T> operator * (T scalar, const Vec2<T>& vector) noexcept { return vector * scalar; }

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

} // namespace dull::util
