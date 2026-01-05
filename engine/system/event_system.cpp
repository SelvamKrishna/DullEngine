#include "engine/config.hpp"
#include "engine/system/event_system.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::system {

Event::Listener::ID EventSystem::bind(
    std::string_view event_name,
    Event::Callback callback
)
{
    auto listener = std::make_unique<Event::Listener>(std::move(callback));
    Event::Listener::ID id = listener->getID();
    _listeners[std::string{event_name}].emplace_back(std::move(listener));

    if constexpr (config::SHOULD_LOG_EVENT_SYS) ZINFO(
        "Event '{}' binded with Listener '{}'", event_name, id
    );

    return id;
}

void EventSystem::unbind(std::string_view event_name, Event::Listener::ID id)
{
    std::shared_lock lock {_mutex};
    auto it = _listeners.find(event_name);
    if (it == _listeners.end())
    {
        if constexpr (config::SHOULD_LOG_EVENT_SYS) ZWARN(
            "Event '{}' not found in EventSystem", event_name
        );

        return;
    }

    std::erase_if(
        it->second,
        [&id](const std::unique_ptr<Event::Listener>& listener)
        { return listener->getID() == id; }
    );

    if constexpr (config::SHOULD_LOG_EVENT_SYS) ZINFO(
        "Event '{}' unbinded - Listener '{}'", event_name, id
    );

    if (!it->second.empty()) return;

    _listeners.erase(it);
    if constexpr (config::SHOULD_LOG_EVENT_SYS) ZINFO(
        "Event '{}' has 0 listerners, Removed from EventSystem", event_name
    );
}

void EventSystem::emit(const Event &event) const noexcept
{
    auto it = _listeners.find(event.getName());

    if (it == _listeners.end())
    {
        if constexpr (config::SHOULD_LOG_EVENT_SYS) ZWARN(
            "Event '{}' not found in EventSystem", event.getName()
        );
        return;
    }

    if constexpr (config::SHOULD_LOG_EVENT_SYS) ZINFO(
        "Event '{}' emitted to {} listeners", event.getName(), it->second.size()
    );

    for (const auto &LISTENER : it->second) LISTENER->callback(event);
}

void EventSystem::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging EventSystem");

    for (const auto& PAIR : _listeners)
    {
        ZDBG(
            "Event '{}' with {} Listeners",
            zlog::ColorText{PAIR.first.c_str(), zlog::ANSI::Magenta},
            PAIR.second.size()
        );

        for (const auto& LISTENER : PAIR.second) ZDBG("ID({}),", LISTENER->getID());
    }
}

#undef _IF_LOG

} // namespace dull::system
