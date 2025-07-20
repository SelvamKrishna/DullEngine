#pragma once

#include <corecrt_terminate.h>
#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <mutex>
#include <ostream>
#include <utility>

namespace Debug {
static std::mutex log_mutex;

enum class Level : uint8_t { Info, Warn, Error };

template <typename... Args>
void log(Level level, const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(log_mutex);

    const char *prefix = nullptr;
    static std::ostream *out = nullptr;
    static std::ostream &cout_ref = std::cout;
    static std::ostream &cerr_ref = std::cerr;

    switch (level) {
    case Level::Info:
        prefix = "[INFO]";
        out = &cout_ref;
        break;
    case Level::Warn:
        prefix = "[WARN]";
        out = &cerr_ref;
        break;
    case Level::Error:
        prefix = "[ERROR]";
        out = &cerr_ref;
        break;
    }

    *out << prefix << " [" << file << ":" << line << "] " << std::format(fmt, std::forward<Args>(args)...)
         << '\n';

    if (level == Level::Error) {
        std::exit(EXIT_FAILURE);
    }
}

template <typename... Args>
void info(const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    log(Level::Info, file, line, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    log(Level::Warn, file, line, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
[[noreturn]] void error(const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    log(Level::Error, file, line, fmt, std::forward<Args>(args)...);
    std::abort();
}

template <typename... Args>
inline std::string traceMsg(const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    return std::format("[{}:{}] {}", file, line, std::format(fmt, std::forward<Args>(args)...));
}

} // namespace Debug

#ifdef DULL_MODE_DEBUG

#define DULL_INFO(fmt, ...) static_cast<void>(0)
#define DULL_WARN(fmt, ...) static_cast<void>(0)
#define DULL_ERROR(fmt, ...) static_cast<void>(0)

#else

#define DULL_INFO(fmt, ...) Debug::info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define DULL_WARN(fmt, ...) Debug::warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define DULL_ERROR(fmt, ...) Debug::error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif

#define TRACE_MSG(fmt, ...) Debug::traceMsg(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
