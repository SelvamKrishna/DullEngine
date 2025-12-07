#pragma once

#include "engine/core/event.hpp"
#include "engine/misc/string_view_hashing.hpp"

#include <vendor/zutils/log.hpp>
#include <vendor/zutils/test.hpp>

#include <string>
#include <string_view>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

namespace dull::core {

class EventBus final {
    friend class App;

private:
    mutable std::shared_mutex _mutex;

    struct Listener final {
        uint64_t id;
        Event::Callback callback;
    };

    using ListenerMap = std::unordered_map<
        std::string,
        std::vector<Listener>,
        misc::StringHash,
        misc::StringEq
    >;

    EventBus::ListenerMap _listeners;

    explicit EventBus() = default;
    ~EventBus() = default;

public:
    uint64_t bind(std::string_view event_name, Event::Callback callback);
    void     unbind(std::string_view event_name, uint64_t callback_id);
    void     emit(const Event& event) const noexcept;

    template <typename... KVPairs>
    void emit(std::string_view name, KVPairs&&... pairs) const
    {
        Event event = Event{name};
        (event.setData(pairs.first, pairs.second), ...);
        emit(event);
    }

    void logStats() const noexcept;
};

} // namespace dull::core
