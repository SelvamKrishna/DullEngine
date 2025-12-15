#pragma once

#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zlog_v2.hpp>

#include <any>
#include <string>
#include <string_view>
#include <optional>
#include <functional>
#include <cstdint>

namespace dull::core {

class Event final {
private:
    using DataMap = std::unordered_map<
        std::string,
        std::any,
        misc::StringHash,
        misc::StringEq
    >;

    std::string    _name;
    Event::DataMap _data_map;

public:
    using Callback = std::function<void(const class Event&)>;

    Event() = delete;

    Event(Event&&)                 = default;
    Event(const Event&)            = default;
    Event& operator=(Event&&)      = default;
    Event& operator=(const Event&) = default;

    explicit Event(std::string_view name) noexcept : _name{name} {}
    ~Event() = default;

    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }

    template <typename DataT>
    [[nodiscard]]
    std::optional<DataT&> tryGetData(std::string_view key) const noexcept
    {
        if (
            auto it = _data_map.find(key);
            it != _data_map.end()
        ) if (
            const DataT* VALUE = std::any_cast<DataT>(&it->second);
            VALUE != nullptr
        ) return *VALUE;

        ZWARN("Event Data (BAD_CAST): Try get data '{}'", key);
        return std::nullopt;
    }

    template <typename DataT>
    void setData(std::string_view key, DataT&& value)
    {
        _data_map.emplace(key, std::forward<DataT>(value));
    }

    uint64_t bind(Event::Callback callback);
    void     unbind(uint64_t callback_id);
    void     emit() const noexcept;

    void logStats() const noexcept;
};

} // namespace dull::core
