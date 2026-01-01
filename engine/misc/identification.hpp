#pragma once

#include <atomic>
#include <cstdint>

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

template <typename TagT>
class StrongID {
public:
    using NumericT = uint32_t;
    static constexpr NumericT NumericMax = UINT_MAX;

    const NumericT ID;

    [[nodiscard]]
    constexpr operator NumericT() const noexcept { return ID; }

#define _OP_COMP(OPR) \
    [[nodiscard]]     \
    bool operator OPR(const StrongID& other) const noexcept { return ID OPR other.ID; }

    _OP_COMP(==)
    _OP_COMP(!=)
    _OP_COMP(<)
    _OP_COMP(<=)
    _OP_COMP(>)
    _OP_COMP(>=)

#undef _OP_COMP
};

template <typename TagT>
class IDGenerator {
public:
    static StrongID<TagT> generate() noexcept
    {
        static std::atomic<uint32_t> counter {1}; // 0 = invalid

        uint32_t value = counter.fetch_add(1, std::memory_order_relaxed);
        ZASSERT(value != 0 && value != StrongID<TagT>::NumericMax, "NumericIDGenerator exhausted");

        return StrongID<TagT> {value};
    }
};

template <typename TagT>
class Identified {
private:
    StrongID<TagT> _id;
#ifndef NDEBUG
    std::string _name;
#endif

public:
    explicit Identified(std::string name) noexcept
    : _id {IDGenerator<TagT>::generate()}
    #ifndef NDEBUG
    , _name {std::move(name)}
    #endif
    { (void)name; }

    [[nodiscard]]
    const StrongID<TagT>& getID() const noexcept { return _id; }

    [[nodiscard]]
    std::string_view getName() const noexcept
    {
    #ifndef NDEBUG
        return _name;
    #else
        return "";
    #endif
    }
};

} // namespace dull::misc
