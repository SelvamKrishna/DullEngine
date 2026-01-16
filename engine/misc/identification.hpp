#pragma once

#include <atomic>
#include <cstdint>

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

// =======================
// Strongly Typed ID
// =======================
template <typename TagT>
class StrongID {
public:
    using Number = uint32_t;
    static constexpr Number NumericMax = UINT_MAX;

    Number id; //< The raw ID value

    StrongID(Number value) : id {value} {}

    // Get an invalid ID
    static constexpr StrongID invalid() noexcept { return StrongID {0}; }

    // Check if ID is valid (non-zero)
    [[nodiscard]]
    constexpr bool isValid() const noexcept { return id != 0; }

    [[nodiscard]]
    constexpr operator Number() const noexcept { return id; }

// Comparison with another StrongID
#define _OP_COMP(OPR) \
    [[nodiscard]]     \
    bool operator OPR(const StrongID& other) const noexcept { return id OPR other.id; }

// Comparison with raw ID
#define _OP_COMP_RAW(OPR) \
    [[nodiscard]]     \
    bool operator OPR(Number other) const noexcept { return id OPR other; }

    _OP_COMP(==)
    _OP_COMP(!=)
    _OP_COMP(<)
    _OP_COMP(<=)
    _OP_COMP(>)
    _OP_COMP(>=)

    _OP_COMP_RAW(==)
    _OP_COMP_RAW(!=)
    _OP_COMP_RAW(<)
    _OP_COMP_RAW(<=)
    _OP_COMP_RAW(>)
    _OP_COMP_RAW(>=)

#undef _OP_COMP
#undef _OP_COMP_RAW
};

// Output Stream support for StrongID
template <typename TagT>
inline std::ostream &operator<<(std::ostream &os, const StrongID<TagT> &id)
{
    return os << (uint64_t)id.id;
}

// =======================
// Strong ID Generator
// =======================
template <typename TagT>
class IDGenerator {
public:
    // Generate a new unique StrongID
    static StrongID<TagT> generate() noexcept
    {
        static std::atomic<uint32_t> counter {1}; // 0 = invalid

        uint32_t value = counter.fetch_add(1, std::memory_order_relaxed);
        ZASSERT(
            value != 0 && value != StrongID<TagT>::NumericMax,
            "NumericIDGenerator exhausted"
        );

        return StrongID<TagT> {value};
    }
};

// =======================
// Identified Base Class
// =======================
template <typename TagT>
class Identified {
private:
    const StrongID<TagT> _ID; //< The unique ID of the object
#ifndef NDEBUG
    std::string _name; //< The debug name of the object
#endif

public:
    using Tag = TagT;
    using ID = StrongID<TagT>;

    explicit Identified(std::string name) noexcept
    : _ID {IDGenerator<TagT>::generate()} // Generate unique ID
#ifndef NDEBUG
    , _name {std::move(name)}
#endif
    { (void)name; }

    [[nodiscard]]
    const StrongID<TagT>& getID() const noexcept { return _ID; }

// Debug name access returns Name in debug builds, ID in release builds
#ifndef NDEBUG
    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }
#else
    [[nodiscard]]
    std::string getName() const noexcept { return std::format("#{}", _id); }
#endif
};

} // namespace dull::misc

template <typename TagT>
struct std::formatter<dull::misc::StrongID<TagT>> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const dull::misc::StrongID<TagT> &id, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", (uint64_t)id.id);
    }
};
