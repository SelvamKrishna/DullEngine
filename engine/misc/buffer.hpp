#pragma once

#include <vendor/zlog_v2.hpp>

#include <memory>

namespace dull::misc {

// =======================
// String Hashed owned collection of Data
// =======================
template <typename DataT>
class Buffer {
private:
    std::vector<std::unique_ptr<DataT>> _buffer;

public:
    // Checks if key already exists
    bool hasData(std::string_view key) const { return _buffer.find(key) != _buffer.end(); }

    // Loads data and returns `true` if done succesfully
    bool loadData(std::string_view key, std::unique_ptr<DataT> data)
    {
        if (!data) return false;
        auto [it, inserted] = _buffer.emplace(key, std::move(data));
        return inserted;
    }

    // Unloads data and returns `true` if done succesfully
    bool unloadData(std::string_view key) { return _buffer.erase(key) > 0; }

    /// TODO: Need to implement `zerr` library for better error handling
    [[nodiscard]]
    DataT& getData(std::string_view key)
    {
        auto it = _buffer.find(key);
        ZASSERT(it != _buffer.end(), "Trying to get unloaded data");
        return *it->second;
    }

    /// TODO: Need to implement `zerr` library for better error handling
    [[nodiscard]]
    const DataT& getData(std::string_view key) const
    {
        auto it = _buffer.find(key);
        ZASSERT(it != _buffer.end(), "Trying to get unloaded data");
        return *it->second;
    }
};

} // namespace dull::misc
