#pragma once

#include "engine/config.hpp"
#include "engine/misc/identification.hpp"

#include <vendor/zlog_v2.hpp>

#include <functional>

// Forward Declaration
namespace dull::system { class EventSystem; }

namespace dull::misc {

// =======================
// Event Channel for a specific Event Type
// =======================
template <typename EventT>
class EventChannel final {
    friend dull::system::EventSystem;

    using Callback = std::function<void(const EventT&)>; //< Function to call when emitted
    struct ListenerTag {};

public:
    // =======================
    // Identified wrapper for Event Callback function
    // =======================
    class Listener : public misc::Identified<ListenerTag> {
    public:
        Callback callback; //< Function to call when event is emitted

        Listener(zlog::internal::ProString desc, Callback callback)
        : misc::Identified<ListenerTag> {desc.isEmpty() ? "<no-desc>" : desc.TEXT}
        , callback {std::move(callback)} {}
    };

private:
    std::vector<std::unique_ptr<Listener>> _listeners; //< List of all subscribed Listeners

public:
    // Subscribe Listener to the Event Channel
    Listener::ID subscribe(
        Callback callback,
        zlog::internal::ProString desc = std::string_view{}
    ) noexcept
    {
        _listeners.emplace_back(std::make_unique<Listener>(desc, callback));

        if constexpr (config::SHOULD_LOG_EVENT_SYS)
            ZINFO("Listener '{}' binded to EventChannel", _listeners.back()->getName());

        return _listeners.back()->getID();
    }

    // Unsubscribe Listener from the Event Channel using its ID
    void unsubscribe(Listener::ID listener_id) noexcept
    {
        if (!listener_id.isValid()) return;

        typename std::vector<std::unique_ptr<Listener>>::iterator it = std::find_if(
            _listeners.begin(),
            _listeners.end(),
            [listener_id](const std::unique_ptr<Listener>& listener) { return listener->getID() == listener_id; }
        );

        ZASSERT(it != _listeners.end(), "Listener '{}' not found!", listener_id);

        if constexpr (config::SHOULD_LOG_EVENT_SYS)
            ZINFO("Listener '{}' unbinded from EventChannel", (*it)->getName());

        _listeners.erase(it);
    }
};

} // namespace dull::misc
