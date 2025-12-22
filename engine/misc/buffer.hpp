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
    using Map = std::unordered_map<
        std::string,
        std::unique_ptr<DataT>,
        misc::StringHash,
        misc::StringEq
    >;

    Map _buffer;

public:
    bool loadData(std::string_view key, std::unique_ptr<DataT> data)
    {
        auto [it, inserted] = _buffer.emplace(key, std::move(data));
        return inserted;
    }

    bool unloadData(std::string_view key) { return _buffer.erase(key) > 0; }

    [[nodiscard]]
    std::unique_ptr<DataT>& getData(std::string_view key) noexcept
    {
        auto it = _buffer.find(key);
        return it != _buffer.end()
        ? it->second.get()
        : std::unique_ptr<DataT>{};
    }

    [[nodiscard]]
    const std::unique_ptr<DataT>& getData(std::string_view key) const noexcept
    {
        auto it = _buffer.find(key);
        return it != _buffer.end()
        ? it->second.get()
        : std::unique_ptr<DataT>{};
    }
};

} // namespace dull::misc
