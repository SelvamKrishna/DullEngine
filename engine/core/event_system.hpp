#pragma once

#include "engine/core/event.hpp"
#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zlog_v2.hpp>

#include <string>
#include <string_view>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

namespace dull::core {

// =======================
// Controls all event related logic
// =======================
class EventSystem final {
    friend class App;

private:
    mutable std::shared_mutex _mutex;

    struct Listener final {
        uint64_t id;              //< Listener ID (UNIQUE)
        Event::Callback callback; //< Function to call when Event emitted
    };

    using ListenerMap = std::unordered_map<
        std::string,           //< Event name (UNIQUE)
        std::vector<Listener>, //< List of all subscribed Listeners
        misc::StringHash,
        misc::StringEq
    >;

    EventSystem::ListenerMap _listeners; //< event_name: listeners[]

    explicit EventSystem() = default;
    ~EventSystem() = default;

public:
    // Link Event with Callback function
    // Returns the ID of the created Listener (UNIQUE)
    uint64_t bind  (std::string_view event_name, Event::Callback callback);

    // Unlink Event with Callback function using the ListenerID
    void     unbind(std::string_view event_name, uint64_t callback_id);
    void     emit(const Event& event) const noexcept;

    // Link Event with Callback function
    // Creates an instant Event with given context
    // Returns the ID of the created Listener (UNIQUE)
    template <typename... KVPairs>
    void emit(std::string_view name, KVPairs&&... pairs) const
    {
        Event event = Event{name};
        (event.setData(pairs.first, pairs.second), ...);
        event.emit();
    }

    // DEV: logs all loaded events and their listeners
    void logStats() const noexcept;
};

} // namespace dull::core
