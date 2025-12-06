#pragma once

#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zutils/log.hpp>
#include <vendor/zutils/test.hpp>

#include <any>
#include <string>
#include <string_view>
#include <shared_mutex>
#include <optional>
#include <functional>
#include <unordered_map>
#include <vector>
#include <utility>

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
    DataT& getData(std::string_view key) const
    {
        auto it = _data_map.find(key);
        ZASSERT_NE(it, _data_map.end());

        const DataT* VALUE = std::any_cast<DataT>(&it->second);
        ZASSERT_NE(VALUE, nullptr);

        return *VALUE;
    }

    template <typename DataT>
    [[nodiscard]]
    std::optional<DataT> tryGetData(std::string_view key) const noexcept
    {
        if (
            auto it = _data_map.find(key);
            it != _data_map.end()
        ) if (
            const DataT* VALUE = std::any_cast<DataT>(&it->second);
            VALUE != nullptr
        ) return *VALUE;

        ZERR("Event Data (BAD_CAST): Try get data '{}'", key);
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

class EventBus final {
    friend class App;

private:
    mutable std::shared_mutex _mutex;

    struct Listener final {
        uint64_t id;
        Event::Callback callback;
    };

    using ListenerMap = std::unordered_map<
        std::string,
        std::vector<Listener>,
        misc::StringHash,
        misc::StringEq
    >;

    EventBus::ListenerMap _listeners;

    explicit EventBus() = default;
    ~EventBus() = default;

public:
    uint64_t bind(std::string_view event_name, Event::Callback callback);
    void     unbind(std::string_view event_name, uint64_t callback_id);
    void     emit(const Event& event) const noexcept;

    template <typename... KVPairs>
    void emit(std::string_view name, KVPairs&&... pairs) const
    {
        Event event = Event{name};
        (event.setData(pairs.first, pairs.second), ...);
        emit(event);
    }

    void logStats() const noexcept;
};

} // namespace dull::core
