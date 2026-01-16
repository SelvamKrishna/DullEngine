#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/misc/identification.hpp"

#include <vendor/zlog_v2.hpp>

#include <functional>

namespace dull::misc {

struct EventListenerTag {};

template <typename EventT>
class EventChannel {
public:
    using Callback = std::function<void(const EventT&)>; //< Function to call when emitted

    // =======================
    // Identified wrapper for Event Callback
    // =======================
    class Listener : public misc::Identified<EventListenerTag> {
    /// TODO: Make it scoped auto remove from buffer when Listener goes out of scope
    public:
        Callback callback;

        Listener(Callback callback)
        : misc::Identified<EventListenerTag> {""}, callback {std::move(callback)}
        {}
    };

private:
    Buffer<Listener> _listeners;

public:
    [[nodiscard]]
    Listener::ID subscribe(Callback callback) noexcept
    {
        std::unique_ptr<Listener> listener {std::make_unique<Listener>(std::move(callback))};
        const typename Listener::ID ID = listener->getID();
        _listeners.add(std::move(listener));
        return ID;
    }

    void unsubscribe(Listener::ID listener_id) noexcept
    {
        ZASSERT(
            _listeners.remove(listener_id),
            "Event Listener '{}' not found.", listener_id
        );
    }

    void emit(const EventT& event) noexcept
    {
        for (std::unique_ptr<Listener>& listener : _listeners) listener->callback(event);
    }
};

} // namespace dull::misc
