#include "engine/core/app.hpp"
#include "engine/system/event.hpp"

#include <vendor/zlog_v2.hpp>

namespace dull::system {

#define _EVENT_BUS  DULL_CTX.event_sys

Event::Listener::ID Event::bind(Event::Callback callback)
{
    return _EVENT_BUS.bind(_name, std::move(callback));
}

void Event::unbind(Listener::ID id)
{
    return _EVENT_BUS.unbind(_name, id);
}

void Event::emit() const noexcept
{
    return _EVENT_BUS.emit(*this);
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

} // namespace dull::system
