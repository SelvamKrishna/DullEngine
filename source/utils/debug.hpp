#pragma once

#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <mutex>
#include <ostream>
#include <utility>

namespace Debug {
static std::mutex log_mutex;

enum class Level : uint8_t { Info, Warn, Err };

template <typename... Args>
void log(Level level, const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);

    const char *prefix = [level] {
        switch (level) {
        case Level::Info:
            return "[INFO]";
        case Level::Warn:
            return "[WARN]";
        case Level::Err:
            return "[ERROR]";
        default:
            return "[UNKNOWN]";
        }
    }();

    std::ostream &out = (level == Level::Info) ? std::cout : std::cerr;
    out << prefix << " [" << file << ":" << line << "] " << std::format(fmt, std::forward<Args>(args)...)
        << '\n';

    if (level == Level::Err) [[unlikely]] {
        std::abort();
    }
}

template <typename... Args>
std::string traceMsg(const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    return std::format("[{}:{}] {}", file, line, std::format(fmt, std::forward<Args>(args)...));
}

} // namespace Debug

#ifdef DULL_MODE_DEBUG
#define DULL_INFO(fmt, ...) ((void)0)
#define DULL_WARN(fmt, ...) ((void)0)
#define DULL_ERROR(fmt, ...) ((void)0)
#else
#define DULL_INFO(fmt, ...) Debug::log(Debug::Level::Info, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#define DULL_WARN(fmt, ...) Debug::log(Debug::Level::Warn, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#define DULL_ERROR(fmt, ...) Debug::log(Debug::Level::Err, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#endif

#define TRACE_MSG(fmt, ...) Debug::traceMsg(__FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)