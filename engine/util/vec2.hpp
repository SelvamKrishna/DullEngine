#pragma once

#include <vendor/raylib.h>

#include <cmath>
#include <type_traits>

namespace dull::util {

template <typename T>
requires std::is_arithmetic_v<T>
struct Vec2 {
    T x {0};
    T y {0};

/// --- Constructors ---

    constexpr Vec2() noexcept = default;
    constexpr Vec2(T x, T y) noexcept : x{x}, y{y} {}

    constexpr Vec2(const rl::Vector2& rl_vec) noexcept
    : x{static_cast<T>(rl_vec.x)}, y{static_cast<T>(rl_vec.y)} {}

/// --- Constants / Factory methods ---

#define _FACTORY(NAME, X, Y) \
    static constexpr Vec2 NAME() noexcept { return Vec2{X, Y}; }

    _FACTORY(kZero ,  0,  0)
    _FACTORY(kOne  ,  1,  1)
    _FACTORY(kUp   ,  0,  1)
    _FACTORY(kDown ,  0, -1)
    _FACTORY(kLeft , -1,  0)
    _FACTORY(kRight,  1,  0)

#undef _FACTORY

    static constexpr Vec2 kUnit(T val = 1) noexcept { return {val, val}; }

/// --- Vector math ---

    [[nodiscard]]
    constexpr T dot(const Vec2& other) const noexcept { return x * other.x + y * other.y; }

    [[nodiscard]]
    constexpr T cross(const Vec2& other) const noexcept { return x * other.y - y * other.x; }

    [[nodiscard]]
    constexpr T lengthSquared() const noexcept { return x * x + y * y; }

    [[nodiscard]]
    T length() const noexcept { return std::sqrt(static_cast<double>(lengthSquared())); }

    [[nodiscard]]
    Vec2 normalized() const noexcept
    {
        const T LEN = static_cast<T>(length());
        return LEN ? (*this / LEN) : kZero();
    }

    void normalize() noexcept { *this = normalized(); }

    [[nodiscard]]
    constexpr Vec2 perpendicular() const noexcept { return {-y, x}; }

    [[nodiscard]]
    constexpr T distanceSquared(const Vec2& other) const noexcept
    {
        return (*this - other).lengthSquared();
    }

    [[nodiscard]]
    T distance(const Vec2& other) const noexcept
    {
        return std::sqrt(static_cast<double>(distanceSquared(other)));
    }

    [[nodiscard]]
    bool nearlyEquals(const Vec2& other, T epsilon = static_cast<T>(1e-6)) const noexcept
    {
        if constexpr (std::is_floating_point_v<T>)
            return std::fabs(x - other.x) < epsilon && std::fabs(y - other.y) < epsilon;
    }

/// --- Operators ---

    [[nodiscard]]
    constexpr Vec2 operator-() const noexcept { return {-x, -y}; }

/// Vec2 (op) Vec2
#define _OP_VEC_VEC(OPR) \
    [[nodiscard]] \
    constexpr Vec2 operator OPR (const Vec2& other) const noexcept \
    { return {x OPR other.x, y OPR other.y}; } \
    constexpr Vec2& operator OPR##= (const Vec2& other) noexcept \
    { x OPR##= other.x; y OPR##= other.y; return *this; } \

    _OP_VEC_VEC(+)
    _OP_VEC_VEC(-)
    _OP_VEC_VEC(*)
    _OP_VEC_VEC(/)

#undef _OP_VEC_VEC

/// Vec2 (op) scalar
#define _OP_VEC_SCL(OPR) \
    [[nodiscard]] \
    constexpr Vec2 operator OPR (T scalar) const noexcept \
    { return {x OPR scalar, y OPR scalar}; } \
    constexpr Vec2& operator OPR##= (T scalar) noexcept \
    { x OPR##= scalar; y OPR##= scalar; return *this; } \

    _OP_VEC_SCL(+)
    _OP_VEC_SCL(-)
    _OP_VEC_SCL(*)
    _OP_VEC_SCL(/)

#undef _OP_VEC_SCL

    constexpr bool operator==(const Vec2& other) const noexcept = default;
    constexpr bool operator!=(const Vec2& other) const noexcept = default;

/// --- Conversion ---

    [[nodiscard]]
    constexpr operator rl::Vector2() const noexcept
    {
        return {static_cast<float>(x), static_cast<float>(y)};
    }
};

/// scalar (op) Vec2
#define _OP_SCL_VEC(OPR) \
    template <typename T> \
    [[nodiscard]] \
    constexpr Vec2<T> operator OPR(T scalar, const Vec2<T>& vec) noexcept { return vec OPR scalar; }

_OP_SCL_VEC(+)
_OP_SCL_VEC(*)

#undef _OP_SCL_VEC

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;

} // namespace dull::util
