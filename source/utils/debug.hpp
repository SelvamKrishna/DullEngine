#pragma once

#include <cstdint>
#include <cstdlib>
#include <format>
#include <iostream>
#include <mutex>
#include <ostream>
#include <source_location>
#include <string>
#include <string_view>
#include <utility>

namespace Debug {
static std::mutex mutex;

enum class Level : uint8_t { Info, Warn };

template <typename... Args>
void log(Level level, const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    std::lock_guard<std::mutex> lock(mutex);

    const char *prefix = [level] {
        switch (level) {
        case Level::Info:
            return "[INFO]";
        case Level::Warn:
            return "[WARN]";
        default:
            return "[UNKNOWN]";
        }
    }();

    std::ostream &out = level == Level::Info ? std::cout : std::cerr;

    out << "[DULL]: " << prefix << " [" << file << ":" << line << "] "
        << std::format(fmt, std::forward<Args>(args)...) << '\n';
}

template <typename... Args>
std::string traceMsg(const char *file, int line, std::format_string<Args...> fmt, Args &&...args) {
    return std::format("[{}:{}] {}", file, line, std::format(fmt, std::forward<Args>(args)...));
}
} // namespace Debug

#ifdef DULL_MODE_DEBUG
#define DULL_INFO(fmt, ...) ((void)0)
#define DULL_WARN(fmt, ...) as((void)0)
#define DULL_ERROR(fmt, ...) as((void)0)
#else
#define DULL_INFO(fmt, ...) Debug::log(Debug::Level::Info, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#define DULL_WARN(fmt, ...) Debug::log(Debug::Level::Warn, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#define DULL_ERROR(fmt, ...) Debug::log(Debug::Level::Err, __FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)
#endif

#define TRACE_MSG(fmt, ...) Debug::traceMsg(__FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)

struct ErrorCtx {
private:
    std::string _operation;
    std::source_location _location;

    enum class FailType : uint8_t { Warning, Critikal };

    void _loggingHelper(FailType fail_type, std::string_view fail_reason) const noexcept {
        std::cerr << std::format("[DULL] [{}] {}:{} - {}: {}\n",
                                 fail_type == FailType::Warning ? "WARNING" : "CRITIKAL",
                                 _location.file_name(),
                                 _location.line(),
                                 _operation,
                                 fail_reason);
    }

public:
    explicit ErrorCtx(std::string operation, std::source_location loc = std::source_location::current())
        : _operation(std::move(operation)), _location(loc) {}

    ErrorCtx(const ErrorCtx &) = delete;
    ErrorCtx(ErrorCtx &&) = delete;
    ErrorCtx &operator=(const ErrorCtx &) = delete;
    ErrorCtx &operator=(ErrorCtx &&) = delete;

    void failFallback(std::string_view fail_reason) const noexcept {
        _loggingHelper(FailType::Warning, fail_reason);
    }

    [[noreturn]] void failExit(std::string_view fail_reason) const noexcept {
        _loggingHelper(FailType::Critikal, fail_reason);
        std::abort();
    }
};