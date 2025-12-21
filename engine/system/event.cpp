#include "engine/core/app.hpp"
#include "engine/system/event.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::sys {

#define _EVENT_BUS  DULL_CTX.event_sys

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

void Event::logStats() const noexcept
{
    ZON_RELEASE return;
    ZTRC_S("Logging Event '{}'", _name);
    for (const auto& DATA : _data_map)
    {
        ZDBG(
            "{}{}",
            zlog::config::TAB_TAG,
            zlog::ColorText{DATA.first, zlog::ANSI::EX_White}
        );
    }
}

#undef _EVENT_BUS

} // namespace dull::sys
