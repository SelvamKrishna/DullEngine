#pragma once

#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zlog_v2.hpp>

#include <string>
#include <memory>
#include <unordered_map>

namespace dull::misc {

template <typename DataT>
class Buffer {
private:
    std::unordered_map<
        std::string,
        std::unique_ptr<DataT>,
        misc::StringHash,
        misc::StringEq
    > _buffer;

public:
    bool hasData(std::string_view key) const
    {
        return _buffer.find(std::string{key}) != _buffer.end();
    }

    bool loadData(std::string_view key, std::unique_ptr<DataT> data)
    {
        if (!data) return false;
        auto [it, inserted] = _buffer.emplace(std::string{key}, std::move(data));
        return inserted;
    }

    bool unloadData(std::string_view key)
    {
        return _buffer.erase(std::string{key}) > 0;
    }

    [[nodiscard]]
    DataT& getData(std::string_view key)
    {
        auto it = _buffer.find(std::string{key});
        ZASSERT(it != _buffer.end(), "Trying to get unloaded data");
        return *it->second;
    }

    [[nodiscard]]
    const DataT& getData(std::string_view key) const
    {
        auto it = _buffer.find(std::string{key});
        ZASSERT(it != _buffer.end(), "Trying to get unloaded data");
        return *it->second;
    }
};

} // namespace dull::misc
