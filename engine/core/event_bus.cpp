#include "engine/config.hpp"
#include "engine/core/event_bus.hpp"

#include <vendor/zlog_v2.hpp>

#include <atomic>

namespace dull::core {

#define _IF_LOG  if constexpr (::dull::config::SHOULD_LOG_EVENT_SYS)

uint64_t EventBus::bind(std::string_view event_name, Event::Callback callback)
{
    std::unique_lock lock {_mutex};

    static std::atomic<uint64_t> s_next {1};
    uint64_t id = s_next++;

    _listeners[std::string{event_name}].emplace_back(Listener{id, std::move(callback)});

    _IF_LOG ZINFO("Event '{}' binded - Listener '{}'", event_name, id);

    return id;
}

void EventBus::unbind(std::string_view event_name, uint64_t id)
{
    std::shared_lock lock {_mutex};

    auto it = _listeners.find(event_name);
    if (it == _listeners.end())
    {
        _IF_LOG ZWARN("Event '{}' not found in EventBus", event_name);
        return;
    }

    std::erase_if(it->second, [&id](const Listener &listener) { return listener.id == id; });

    _IF_LOG ZINFO("Event '{}' unbinded - Listener '{}'", event_name, id);

    if (!it->second.empty()) return;

    _listeners.erase(it);
    _IF_LOG ZINFO("Event '{}' has 0 listerners, Removed from EventBus", event_name);
}

void EventBus::emit(const Event &event) const noexcept
{
    auto it = _listeners.find(event.getName());

    if (it == _listeners.end())
    {
        _IF_LOG ZWARN("Event '{}' not found in EventBus", event.getName());
        return;
    }

    _IF_LOG ZINFO("Event '{}' emitted to {} listeners", event.getName(), it->second.size());
    for (const auto &LISTENER : it->second) LISTENER.callback(event);
}

void EventBus::logStats() const noexcept
{
    ZON_RELEASE return;

    for (const auto& PAIR : _listeners)
    {
        ZDBG(
            "Event '{}' with {} Listeners",
            zlog::ColorText{PAIR.first.c_str(), zlog::ANSI::Magenta},
            PAIR.second.size()
        );

        for (const auto& LISTENER : PAIR.second)
            ZDBG("ID({}),", LISTENER.id);
    }
}

#undef _IF_LOG

} // namespace dull::core
