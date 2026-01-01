#pragma once

#include <atomic>
#include <cstdint>

#include <vendor/zlog_v2.hpp>

namespace dull::misc {

template <typename TagT>
class StrongID {
public:
    using NumericT = uint32_t;
    static constexpr NumericT NumericMax = UINT32_MAX;

    const NumericT ID;

    [[nodiscard]]
    constexpr operator NumericT() const noexcept { return ID; }
};

template <typename TagT>
class IDGenerator {
public:
    static StrongID<TagT> generate() noexcept
    {
        static std::atomic<uint32_t> counter {1}; // 0 = invalid

        uint32_t value = counter.fetch_add(1, std::memory_order_relaxed);
        ZASSERT(value != 0 && value != UINT32_MAX, "NumericIDGenerator exhausted");

        return StrongID<TagT> {value};
    }
};

template <typename TagT>
class Identified {
private:
#ifndef NDEBUG
    std::string _name;
#endif
    StrongID<TagT> _id {};

public:
#ifndef NDEBUG
    explicit Identified(std::string name) noexcept
    : _name {std::move(name)}
    , _id {IDGenerator<TagT>::generate()}
    {}
#else
    explicit Identified(std::string = {}) noexcept
    : _id {IDGenerator<TagT>::generate()}
    {}
#endif

    [[nodiscard]]
    const StrongID<TagT>& getID() const noexcept { return _id; }

#ifndef NDEBUG
    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }
#endif
};

} // namespace dull::misc
