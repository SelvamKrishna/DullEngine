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
class EventChannel {
    friend dull::system::EventSystem;
    using Callback = std::function<void(const EventT&)>; //< Function to call when emitted

private:
    struct ListenerTag {};

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

    std::vector<Listener> _listeners; //< List of all subscribed Listeners

public:
    // =======================
    // RAII wrapper for automatic unsubscription
    // =======================
    class ScopedListener {
    private:
        EventChannel* _channel = nullptr; //< Parent Event Channel
        const Listener::ID _ID;           //< ID of the subscribed Listener

    public:
        ScopedListener(EventChannel* channel, Listener::ID id) noexcept
        : _channel(channel), _ID(id) {}

        ~ScopedListener() noexcept { unbind(); }

        ScopedListener(const ScopedListener&) = delete;
        ScopedListener& operator=(const ScopedListener&) = delete;

        ScopedListener(ScopedListener&& other) noexcept
        : _channel(other._channel), _ID(other._ID) { other._channel = nullptr; }

        ScopedListener& operator=(ScopedListener&& other) noexcept
        {
            if (this != &other) [[likely]]
            {
                unbind();
                _channel = other._channel;
                _ID = other._ID;
                other._channel = nullptr;
            }

            return *this;
        }

        // Unsubscribe the Listener from the Event Channel
        void unbind() noexcept
        {
            if (_channel == nullptr) return;
            _channel->unsubscribe(_ID);
            _channel = nullptr;
        }
    };

    // Subscribe Listener to the Event Channel
    Listener::ID subscribe(
        Callback callback,
        zlog::internal::ProString desc = std::string_view{}
    ) noexcept
    {
        _listeners.emplace_back(Listener {desc, callback});

        if constexpr (config::SHOULD_LOG_EVENT_SYS)
            ZINFO("Listener '{}' binded to EventChannel", _listeners.back().getName());

        return _listeners.back().getID();
    }

    // Subscribe with automatic unsubscription on destruction
    [[nodiscard]]
    ScopedListener subscribeScoped(
        Callback callback,
        zlog::internal::ProString desc = std::string_view{}
    ) noexcept
    {
        return ScopedListener {this, subscribe(std::move(callback), desc)};
    }

    // Unsubscribe Listener from the Event Channel using its ID
    void unsubscribe(Listener::ID listener_id) noexcept
    {
        typename std::vector<Listener>::iterator it = std::find_if(
            _listeners.begin(),
            _listeners.end(),
            [listener_id](const Listener& listener) { return listener.getID() == listener_id; }
        );

        ZASSERT(it != _listeners.end(), "Listener '{}' not found!", listener_id);

        if constexpr (config::SHOULD_LOG_EVENT_SYS)
            ZINFO("Listener '{}' unbinded from EventChannel", it->getName());

        _listeners.erase(it);
    }
};

} // namespace dull::misc
