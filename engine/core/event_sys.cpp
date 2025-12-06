#include "engine/config.hpp"
#include "engine/core/app.hpp"
#include "engine/core/event_sys.hpp"

#include <vendor/zutils/log.hpp>
#include <vendor/zutils/tools.hpp>

#include <atomic>

namespace dull::core {

#define _EVENT_BUS \
    App::instance().getEventBus()

uint64_t Event::bind(Event::Callback callback)
{
    return _EVENT_BUS.bind(_name, std::move(callback));
}

void Event::unbind(uint64_t id)
{
    return _EVENT_BUS.unbind(_name, id);
}

void Event::emit() const noexcept
{
    return _EVENT_BUS.emit(_name);
}

#undef _EVENT_BUS

void Event::logStats() const noexcept
{
    ZON_RELEASE return;

    ZDBG("Status -> Event ({})", (void*)this);
    ZVAR(_name);
    ZVAR(_data_map.size());

    for (const auto& DATA : _data_map)
        ZDBG("{}{} -> {}", zutils::config::TAB_TAG, DATA.first, (void*)&DATA.second);
}

uint64_t EventBus::bind(std::string_view event_name, Event::Callback callback)
{
    std::unique_lock lock {_mutex};

    static std::atomic<uint64_t> s_next {1};
    uint64_t id = s_next++;

    _listeners[std::string{event_name}].emplace_back(Listener{id, std::move(callback)});
    ZINFO_IF(config::SHOULD_LOG_EVENT_SYS, "Event bind: {} <-> Listener ({})", event_name, id);

    return id;
}

void EventBus::unbind(std::string_view event_name, uint64_t id)
{
    std::shared_lock lock {_mutex};

    auto it = _listeners.find(event_name);
    if (it == _listeners.end())
    {
        ZWARN_IF(
            config::SHOULD_LOG_EVENT_SYS,
            "Event unbind (NOT FOUND): {} <-> Listener (ID: {})",
            event_name, id
        );

        return;
    }

    std::erase_if(it->second, [&id](const Listener &listener) { return listener.id == id; });
    ZINFO_IF(config::SHOULD_LOG_EVENT_SYS, "Event unbind: {} <-> Listener (ID: {})", event_name, id);

    if (!it->second.empty()) return;

    _listeners.erase(it);
    ZINFO_IF(config::SHOULD_LOG_EVENT_SYS, "Event erase: {} has no binded listerners", event_name);
}

void EventBus::emit(const Event &event) const noexcept
{
    if (auto it = _listeners.find(event.getName()); it != _listeners.end())
    {
        ZINFO_IF(config::SHOULD_LOG_EVENT_SYS, "Event emit : {}", event.getName());
        for (const auto &LISTENER : it->second) LISTENER.callback(event);
        return;
    }

    ZWARN_IF(config::SHOULD_LOG_EVENT_SYS, "Event emit (NOT FOUND) : {}", event.getName());
}

void EventBus::logStats() const noexcept
{
    ZON_RELEASE return;

    ZINFO("Status -> EventBus ({})", (void*)this);
    ZVAR(_listeners.size());

    for (const auto& PAIR : _listeners)
    {
        ZDBG(
            "{} : {} Listeners",
            zutils::ColorText{PAIR.first.c_str(), zutils::ANSI::Magenta},
            PAIR.second.size()
        );

        for (const auto& LISTENER : PAIR.second)
            ZDBG("{}ID({}),", zutils::config::TAB_TAG, LISTENER.id);
    }
}

} // namespace dull::core
