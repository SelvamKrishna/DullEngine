#include "engine/config.hpp"
#include "engine/system/event_system.hpp"

#include <vendor/zlog_v2.hpp>

#include <atomic>

namespace dull::system {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_EVENT_SYS)

uint64_t EventSystem::bind(std::string_view event_name, Event::Callback callback)
{
    std::unique_lock lock {_mutex};
    static std::atomic<uint64_t> s_next {1}; // Unique Listener ID
    uint64_t id = s_next++;

    _listeners[std::string{event_name}].emplace_back(Listener{id, std::move(callback)});

    _IF_LOG ZINFO("Event '{}' binded - Listener '{}'", event_name, id);

    return id;
}

void EventSystem::unbind(std::string_view event_name, uint64_t id)
{
    std::shared_lock lock {_mutex};

    auto it = _listeners.find(event_name);
    if (it == _listeners.end())
    {
        _IF_LOG ZWARN("Event '{}' not found in Eventsystemtem", event_name);
        return;
    }

    std::erase_if(it->second, [&id](const Listener &listener) { return listener.id == id; });

    _IF_LOG ZINFO("Event '{}' unbinded - Listener '{}'", event_name, id);

    if (!it->second.empty()) return;

    _listeners.erase(it);
    _IF_LOG ZINFO("Event '{}' has 0 listerners, Removed from Eventsystemtem", event_name);
}

void EventSystem::emit(const Event &event) const noexcept
{
    auto it = _listeners.find(event.getName());

    if (it == _listeners.end())
    {
        _IF_LOG ZWARN("Event '{}' not found in Eventsystemtem", event.getName());
        return;
    }

    _IF_LOG ZINFO("Event '{}' emitted to {} listeners", event.getName(), it->second.size());
    for (const auto &LISTENER : it->second) LISTENER.callback(event);
}

void EventSystem::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging Eventsystemtem");

    for (const auto& PAIR : _listeners)
    {
        ZDBG(
            "Event '{}' with {} Listeners",
            zlog::ColorText{PAIR.first.c_str(), zlog::ANSI::Magenta},
            PAIR.second.size()
        );

        for (const auto& LISTENER : PAIR.second) ZDBG("ID({}),", LISTENER.id);
    }
}

#undef _IF_LOG

} // namespace dull::system
