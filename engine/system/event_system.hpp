#pragma once

#include "engine/misc/string_view_hashing.hpp"
#include "engine/system/event.hpp"

#include <vendor/zlog_v2.hpp>

#include <string>
#include <vector>
#include <string_view>
#include <shared_mutex>
#include <unordered_map>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

// =======================
// Controls all event related logic
// =======================
class EventSystem final {
    friend class dull::core::App;

private:
    mutable std::shared_mutex _mutex;

    using ListenerMap = std::unordered_map<
        std::string, //< Event name (UNIQUE)
        std::vector<std::unique_ptr<Event::Listener>>, //< List of all subscribed Listeners
        misc::StringHash,
        misc::StringEq
    >;

    EventSystem::ListenerMap _listeners; //< event_name: listeners[]

    explicit EventSystem() = default;
    ~EventSystem() = default;

public:
    // Link Event with Callback function
    // Returns the ID of the created Listener (UNIQUE)
    Event::Listener::ID bind(std::string_view event_name, Event::Callback callback);

    // Unlink Event with Callback function using the ListenerID
    void unbind(std::string_view event_name, Event::Listener::ID callback_id);
    void emit(const Event& event) const noexcept;

    // DEV: logs all loaded events and their listeners
    void logStats() const noexcept;
};

} // namespace dull::system
