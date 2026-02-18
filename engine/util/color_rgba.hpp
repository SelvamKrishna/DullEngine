#pragma once

#include <vendor/raylib.h>

#include <cstdint>

namespace dull::util {

struct Color {
    uint8_t r {0};
    uint8_t g {0};
    uint8_t b {0};
    uint8_t a {255};

// --- Constructors ---

    constexpr Color() noexcept = default;

    constexpr Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) noexcept
        : r {r}, g {g}, b {b}, a {a}
    {}

    constexpr Color(const rl::Color& rlColor) noexcept
        : r {rlColor.r}, g {rlColor.g}, b {rlColor.b}, a {rlColor.a}
    {}

// --- Pre-defined Colors ---

    [[nodiscard]] static constexpr Color White  () noexcept { return { 255, 255, 255, 255 }; }
    [[nodiscard]] static constexpr Color Red    () noexcept { return { 255, 0  , 0  , 255 }; }
    [[nodiscard]] static constexpr Color Green  () noexcept { return { 0  , 255, 0  , 255 }; }
    [[nodiscard]] static constexpr Color Blue   () noexcept { return { 0  , 0  , 255, 255 }; }
    [[nodiscard]] static constexpr Color Cyan   () noexcept { return { 0  , 255, 255, 255 }; }
    [[nodiscard]] static constexpr Color Magenta() noexcept { return { 255, 0  , 255, 255 }; }
    [[nodiscard]] static constexpr Color Yellow () noexcept { return { 255, 255, 0  , 255 }; }
    [[nodiscard]] static constexpr Color Black  () noexcept { return { 0  , 0  , 0  , 255 }; }

    [[nodiscard]] static constexpr Color Gray(uint8_t scalar = 255 / 2, uint8_t alpha = 255) noexcept
    {
        return {scalar, scalar, scalar, alpha};
    }

// --- Hex conversions ---

    [[nodiscard]] static constexpr Color FromHex(uint32_t hexValue) noexcept
    {
        return (hexValue <= 0xFFFFFF)
            ? Color { /// RR, GG, BB with max Alpha
                static_cast<uint8_t>((hexValue >> 16) & 0xFF),
                static_cast<uint8_t>((hexValue >>  8) & 0xFF),
                static_cast<uint8_t>( hexValue        & 0xFF),
                255
            }
            : Color { /// RR, GG, BB, AA
                static_cast<uint8_t>((hexValue >> 24) & 0xFF),
                static_cast<uint8_t>((hexValue >> 16) & 0xFF),
                static_cast<uint8_t>((hexValue >>  8) & 0xFF),
                static_cast<uint8_t>( hexValue        & 0xFF)
            }
        ;
    }

    [[nodiscard]] constexpr uint32_t ToHex() const noexcept
    {
        return
            (static_cast<uint32_t>(this->a) << 24) |
            (static_cast<uint32_t>(this->r) << 16) |
            (static_cast<uint32_t>(this->g) << 8)  |
            (static_cast<uint32_t>(this->b) << 0)
        ;
    }

// --- Color utilities ---

    [[nodiscard]] constexpr Color Inverted() const noexcept
    {
        return {
            static_cast<uint8_t>(255 - this->r),
            static_cast<uint8_t>(255 - this->g),
            static_cast<uint8_t>(255 - this->b),
            this->a
        };
    }

    [[nodiscard]] constexpr Color Grayscaled() const noexcept
    {
        constexpr float R_LUMINOSITY = 0.3F;
        constexpr float G_LUMINOSITY = 0.59F;
        constexpr float B_LUMINOSITY = 0.11F;

        return Color::Gray(static_cast<uint8_t>(r * R_LUMINOSITY + g * G_LUMINOSITY + b * B_LUMINOSITY), a);
    }

// --- Operators
// -> Color (op) Color

    constexpr Color operator + (const Color& other) const noexcept
    {
        return {
            static_cast<uint8_t>(this->r + other.r),
            static_cast<uint8_t>(this->g + other.g),
            static_cast<uint8_t>(this->b + other.b),
            static_cast<uint8_t>(this->a + other.a)
        };
    }

    constexpr Color operator - (const Color& other) const noexcept
    {
        return {
            static_cast<uint8_t>(this->r - other.r),
            static_cast<uint8_t>(this->g - other.g),
            static_cast<uint8_t>(this->b - other.b),
            static_cast<uint8_t>(this->a - other.a)
        };
    }

    constexpr Color operator * (const Color& other) const noexcept
    {
        return {
            static_cast<uint8_t>(this->r * other.r / 255),
            static_cast<uint8_t>(this->g * other.g / 255),
            static_cast<uint8_t>(this->b * other.b / 255),
            static_cast<uint8_t>(this->a * other.a / 255)
        };
    }

    constexpr Color operator / (const Color& other) const noexcept
    {
        return {
            static_cast<uint8_t>(other.r ? this->r / other.r : 255),
            static_cast<uint8_t>(other.g ? this->g / other.g : 255),
            static_cast<uint8_t>(other.b ? this->b / other.b : 255),
            static_cast<uint8_t>(other.a ? this->a / other.a : 255)
        };
    }

    constexpr Color& operator+=(const Color& other) noexcept { return *this = *this + other; }
    constexpr Color& operator-=(const Color& other) noexcept { return *this = *this - other; }
    constexpr Color& operator*=(const Color& other) noexcept { return *this = *this * other; }
    constexpr Color& operator/=(const Color& other) noexcept { return *this = *this / other; }

// -> Color (op) Scalar

    constexpr Color operator + (uint8_t scalar) const noexcept { return *this + Color::Gray(scalar); }
    constexpr Color operator - (uint8_t scalar) const noexcept { return *this - Color::Gray(scalar); }
    constexpr Color operator * (uint8_t scalar) const noexcept { return *this * Color::Gray(scalar); }
    constexpr Color operator / (uint8_t scalar) const noexcept { return *this / Color::Gray(scalar); }

    constexpr Color& operator += (uint8_t scalar) noexcept { return *this = *this + scalar; }
    constexpr Color& operator -= (uint8_t scalar) noexcept { return *this = *this - scalar; }
    constexpr Color& operator *= (uint8_t scalar) noexcept { return *this = *this * scalar; }
    constexpr Color& operator /= (uint8_t scalar) noexcept { return *this = *this / scalar; }

// --- Comparison ---

    constexpr bool operator == (const Color& other) const noexcept = default;
    constexpr bool operator != (const Color& other) const noexcept = default;

// --- Conversion ---

    constexpr operator rl::Color() const noexcept { return {this->r, this->g, this->b, this->a}; }
};

} // namespace dull::util
