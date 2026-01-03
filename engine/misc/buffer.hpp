#pragma once

#include "engine/misc/identification.hpp"

#include <vendor/zlog_v2.hpp>

#include <memory>

namespace dull::misc {

template <typename DataT>
    requires std::is_base_of_v<Identified<typename DataT::Tag>, DataT>
class Buffer {
public:
    using iterator       = std::vector<std::unique_ptr<DataT>>::iterator;
    using const_iterator = std::vector<std::unique_ptr<DataT>>::const_iterator;

private:
    std::vector<std::unique_ptr<DataT>> _buffer;

    // Binary search the buffer for the iterator using the ID
    [[nodiscard]]
    const_iterator _searchIterator(const typename DataT::ID& id) const noexcept
    {
        return std::lower_bound(
            _buffer.begin(), _buffer.end(), id,
            [](const std::unique_ptr<DataT>& elem, const typename DataT::ID& id)
            { return elem->getID() < id; }
        );
    }

    // Binary search the buffer for the const iterator using the ID
    [[nodiscard]]
    iterator _searchIterator(const typename DataT::ID& id) noexcept
    {
        return std::lower_bound(
            _buffer.begin(), _buffer.end(), id,
            [](const std::unique_ptr<DataT>& elem, const typename DataT::ID& id)
            { return elem->getID() < id; }
        );
    }

    // Checks if iterator is valid and matches with given ID
    [[nodiscard]]
    bool _isMatchIterator(const_iterator it, const typename DataT::ID& id) const noexcept
    {
        return it != _buffer.end() && (*it)->getID() == id;
    }

public:
    Buffer() = default;
    Buffer(size_t reserve) { _buffer.reserve(reserve); }
    ~Buffer() = default;

    constexpr Buffer(Buffer&&)                 noexcept = default;
    constexpr Buffer(const Buffer&)            noexcept = default;
    constexpr Buffer& operator=(Buffer&&)      noexcept = default;
    constexpr Buffer& operator=(const Buffer&) noexcept = default;

    // Insert a new element into the buffer, keeping it sorted by ID
    bool add(std::unique_ptr<DataT> data)
    {
        if (data == nullptr) [[unlikely]]
        {
            ZWARN("Provided `null` value to Buffer<{}>", typeid(DataT).name());
            return false;
        }

        iterator it = _searchIterator(data->getID());

        if (_isMatchIterator(it, data->getID())) [[unlikely]]
        {
            ZWARN(
                "Data with ID '{}' already exist in value to Buffer<{}>",
                data->getID(), typeid(DataT).name()
            );
            return false;
        }

        _buffer.insert(it, std::move(data));
        return true;
    }

    // Remove element by ID
    bool remove(const typename DataT::ID& id)
    {
        iterator it = _searchIterator(id);

        if (it == _buffer.end() || (*it)->getID() != id)
        {
            ZWARN(
                "Data with ID '{}' not found in Buffer<{}>",
                id, typeid(DataT).name()
            );
            return false;
        }

        _buffer.erase(it);
        return true;
    }

    // Lookup by ID
    DataT* find(const typename DataT::ID& id) noexcept
    {
        iterator it = _searchIterator(id);
        return _isMatchIterator(it, id) ? it->get() : nullptr;
    }

/// --- Iterator ---
    auto begin() noexcept { return _buffer.begin(); }
    auto end() noexcept { return _buffer.end(); }
    auto begin() const noexcept { return _buffer.begin(); }
    auto end() const noexcept { return _buffer.end(); }

/// --- Utility ---
    [[nodiscard]] size_t size() const noexcept { return _buffer.size(); }
    [[nodiscard]] size_t capacity() const noexcept { return _buffer.capacity(); }
    [[nodiscard]] bool empty() const noexcept { return _buffer.empty(); }
    void shrinkToFit() { _buffer.shrink_to_fit(); }
    void clear() { _buffer.clear(); }
};

} // namespace dull::misc
