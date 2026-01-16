#pragma once

#include "engine/misc/event_channel.hpp"

#include <vendor/zlog_v2.hpp>

#include <shared_mutex>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

// =======================
// Controls all event related logic
// =======================
class EventSystem final {
    friend class dull::core::App;

private:
    mutable std::shared_mutex _mutex; //< Thread safety for event channels

    explicit EventSystem() = default;
    ~EventSystem() = default;

public:
    // Access event channel to subscribe/unsubscribe listeners
    template <typename EventT>
    misc::EventChannel<EventT>& getChannel() noexcept
    {
        std::unique_lock lock {_mutex};
        static misc::EventChannel<EventT> channel {};
        return channel;
    }

    // Emit event to all subscribed listeners
    template <typename EventT>
    void emit(const EventT& event) noexcept
    {
        misc::EventChannel<EventT>& channel = getChannel<EventT>();
        for (const auto& LISTENER : channel._listeners) LISTENER.callback(event);
    }
};

} // namespace dull::system
