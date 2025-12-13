#include "engine/core/app.hpp"
#include "engine/core/event.hpp"

#include <vendor/zutils/log.hpp>
#include <vendor/zutils/tools.hpp>

namespace dull::core {

#define _EVENT_BUS \
    ::dull::core::App::instance().getHandle().eventBus()

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

} // namespace dull::core
