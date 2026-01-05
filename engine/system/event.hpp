#pragma once

#include "engine/misc/identification.hpp"
#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zlog_v2.hpp>

#include <any>
#include <string>
#include <string_view>
#include <optional>
#include <functional>

namespace dull::system {

// =======================
// Event with additional Data information
// =======================
class Event final {
private:
    using DataMap = std::unordered_map<
        std::string, //< Name of the variable
        std::any,    //< Content of the variable
        misc::StringHash,
        misc::StringEq
    >;

    std::string _name;
    Event::DataMap _data_map;

    struct EventListenerTag {};

public:
    using Callback = std::function<void(const class Event&)>; // Function to call when emitted

    class Listener : public misc::Identified<EventListenerTag> {
    public:
        Callback callback; //< Function to call when Event emitted

        Listener(Callback callback)
        : misc::Identified<EventListenerTag> {""}, callback {std::move(callback)}
        {}
    };

    Event() = delete;

    Event(Event&&)                 = default;
    Event(const Event&)            = default;
    Event& operator=(Event&&)      = default;
    Event& operator=(const Event&) = default;

    explicit Event(std::string_view name) noexcept : _name{name} {}
    ~Event() = default;

    [[nodiscard]]
    std::string_view getName() const noexcept { return _name; }

    // Used by the Listener to access underlying data
    template <typename DataT>
    [[nodiscard]]
    std::optional<DataT> getData(std::string_view key) const noexcept
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

    // Used by the Sender to add context to the Event
    template <typename DataT>
    void setData(std::string_view key, DataT&& value)
    {
        _data_map.emplace(key, std::forward<DataT>(value));
    }

    // Binds Callback function with Event
    Listener::ID bind(Event::Callback callback);

    // Unbinds Callback function with Event
    void unbind(Listener::ID callback_id);

    // Emits Event calling all the binded callback function
    void emit() const noexcept;

    // DEV: Logs all stores variables
    void logStats() const noexcept;
};

} // namespace dull::system
