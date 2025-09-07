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

[[noreturn]] static inline void _UNREACHABLE() { std::abort(); }

template<typename... Args>
[[noreturn]] static inline void _TODO(std::format_string<Args...> fmt, Args&&... args) {
    std::cerr << "[TODO] " << std::format(fmt, std::forward<Args>(args)...) << std::endl;
    std::abort();
}

namespace Debug {
	static std::mutex mutex;

	enum class Level : uint8_t { Info, Warn, Log };

	template <typename... Args>
	void log(Level level, std::format_string<Args...> fmt, Args&& ...args) {
		std::lock_guard<std::mutex> lock(mutex);

		const char* PREFIX = [level] {
			switch (level) {
				case Level::Info: return "[INFO] ";
				case Level::Warn: return "[WARN] ";
				case Level::Log:  return "[LOG] ";
				default: _UNREACHABLE();
			}
		} ();

		std::ostream& out = level == Level::Info ? std::cout : std::cerr;
		out << "[DULL] " << PREFIX << std::format(fmt, std::forward<Args>(args)...) << '\n';
	}

	template <typename... Args>
	std::string traceMsg(const char* file, int line, std::format_string<Args...> fmt, Args&& ...args) {
		return std::format("[{}:{}] {}", file, line, std::format(fmt, std::forward<Args>(args)...));
	}
}

#ifdef DULL_MODE_DEBUG
#define DULL_INFO(fmt, ...) Debug::log(Debug::Level::Info, fmt __VA_OPT__(, ) __VA_ARGS__)
#define DULL_WARN(fmt, ...) Debug::log(Debug::Level::Warn, fmt __VA_OPT__(, ) __VA_ARGS__)
#else
#define DULL_INFO(fmt, ...) ((void)0)
#define DULL_WARN(fmt, ...) ((void)0)
#endif

#define DULL_LOG(fmt, ...)   Debug::log(Debug::Level::Log, fmt __VA_OPT__(, ) __VA_ARGS__)
#define TRACE_MSG(fmt, ...)  Debug::traceMsg(__FILE__, __LINE__, fmt __VA_OPT__(, ) __VA_ARGS__)

struct ErrorCtx {
private:
	std::string _operation_desc;
	std::source_location _location;

	enum class FailType : uint8_t { Failure, Critikal };

	void _loggingHelper(FailType fail_type, std::string_view fail_reason) const noexcept {
		std::cerr << std::format(
			"[DULL] [{}] {}:{} - {}: {}\n",
			fail_type == FailType::Failure ? "FAILURE" : "CRITIKAL",
			_location.file_name(),
			_location.line(),
			_operation_desc,
			fail_reason
		);
	}

public:
	explicit ErrorCtx(std::string operation_desc = "")
	: _operation_desc(std::move(operation_desc))
	, _location(std::source_location::current()) {}

	ErrorCtx(const ErrorCtx&) = delete;
	ErrorCtx(ErrorCtx&&) = delete;
	ErrorCtx& operator=(const ErrorCtx&) = delete;
	ErrorCtx& operator=(ErrorCtx&&) = delete;

	void setOperationDesc(std::string operation_desc) {
		_operation_desc = std::move(operation_desc);
	}

	void failFallback(std::string_view fail_reason) const noexcept {
		_loggingHelper(FailType::Failure, fail_reason);
	}

	[[noreturn]] void failExit(std::string_view fail_reason) const noexcept {
		_loggingHelper(FailType::Critikal, fail_reason);
		std::abort();
	}
};