#pragma once

#include <cstdlib>
#include <format>
#include <iostream>
#include <utility>

namespace Debug {

enum class Level { Info, Warn, Error };

template <typename... Args>
void log(Level level, const char* file, int line, std::format_string<Args...> fmt, Args&&... args) {
  const char* prefix = nullptr;
  std::ostream* out = nullptr;

  switch (level) {
    case Level::Info:
      prefix = "[INFO]";
      out = &std::cout;
      break;
    case Level::Warn:
      prefix = "[WARN]";
      out = &std::cerr;
      break;
    case Level::Error:
      prefix = "[ERROR]";
      out = &std::cerr;
      break;
  }

  *out << prefix << " [" << file << ":" << line << "] "
       << std::format(fmt, std::forward<Args>(args)...) << '\n';

  if (level == Level::Error) std::exit(EXIT_FAILURE);
}

template <typename... Args>
void info(const char* file, int line, std::format_string<Args...> fmt, Args&&... args) {
  log(Level::Info, file, line, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const char* file, int line, std::format_string<Args...> fmt, Args&&... args) {
  log(Level::Warn, file, line, fmt, std::forward<Args>(args)...);
}

template <typename... Args>
[[noreturn]] void error(const char* file,
                        int line,
                        std::format_string<Args...> fmt,
                        Args&&... args) {
  log(Level::Error, file, line, fmt, std::forward<Args>(args)...);
}

}  // namespace Debug

#define DULL_INFO(fmt, ...) Debug::info(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define DULL_WARN(fmt, ...) Debug::warn(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define DULL_ERROR(fmt, ...) Debug::error(__FILE__, __LINE__, fmt, ##__VA_ARGS__)

template <typename... Args>
inline std::string trace_msg(const char* file,
                             int line,
                             std::format_string<Args...> fmt,
                             Args&&... args) {
  return std::format("[{}:{}] {}", file, line, std::format(fmt, std::forward<Args>(args)...));
}

#define TRACE_MSG(fmt, ...) trace_msg(__FILE__, __LINE__, fmt, ##__VA_ARGS__)
