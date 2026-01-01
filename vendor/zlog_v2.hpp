#pragma once

/*

=== ZLOG -> C++ 23 LOGGING LIBRARY ===

--- Details ---

version: 2
date:    20-12-2025
author:  https://www.github.com/SelvamKrishna

*/

#include <format>
#include <ostream>
#include <string_view>

namespace zlog {

// Logging severity levels
enum class LogLevel : uint8_t {
    Trace,  //< Detailed trace information for debugging
    Debug,  //< Debug-level information for development
    Info,   //< General informational messages
    Warn,   //< Warning messages indicating potential issues
    Error,  //< Error messages indicating failures
    Fatal,  //< Fatal errors causing program termination
};

// ANSI escape codes for terminal styling
enum class ANSI : uint8_t {
// =============== TEXT ATTRIBUTES ===============
    Reset          = 0,
    Bold           = 1,
    Dim            = 2,
    Italic         = 3,
    Underline      = 4,
    Blink          = 5,
    Inverse        = 7,
    Hidden         = 8,
    Strikethrough  = 9,
// =============== REGULAR COLORS ===============
    Black          = 30,
    Red            = 31,
    Green          = 32,
    Yellow         = 33,
    Blue           = 34,
    Magenta        = 35,
    Cyan           = 36,
    White          = 37,
// =============== BACKGROUND COLORS ===============
    BG_Black       = 40,
    BG_Red         = 41,
    BG_Green       = 42,
    BG_Yellow      = 43,
    BG_Blue        = 44,
    BG_Magenta     = 45,
    BG_Cyan        = 46,
    BG_White       = 47,
// =============== BRIGHT COLORS ===============
    EX_Black       = 90,
    EX_Red         = 91,
    EX_Green       = 92,
    EX_Yellow      = 93,
    EX_Blue        = 94,
    EX_Magenta     = 95,
    EX_Cyan        = 96,
    EX_White       = 97,
// =============== BRIGHT BACKGROUND COLORS ===============
    BG_EX_Black    = 100,
    BG_EX_Red      = 101,
    BG_EX_Green    = 102,
    BG_EX_Yellow   = 103,
    BG_EX_Blue     = 104,
    BG_EX_Magenta  = 105,
    BG_EX_Cyan     = 106,
    BG_EX_White    = 107,
};

// ANSI color coded text with associated text and color code.
struct ColorText {
    const std::string_view TEXT;   //< The text content to display
    const ANSI             COLOR;  //< ANSI color code for the text
};

namespace config {

// === MODIFY THESE VALUES ===

// General flags
static constexpr bool DISABLE_LOGGING   = false;  // Completely disable logging
static constexpr bool ENABLE_TIMESTAMP  = false;  // Add [HH:MM:SS] to logs
static constexpr bool ENABLE_COLOR      = true;   // Enable ANSI colors
static constexpr bool ENABLE_TRACE_DULL = true;   // Make trace messages gray

// Minimum log levels
static constexpr LogLevel MIN_LVL_RLS = LogLevel::Info;   // Release builds
static constexpr LogLevel MIN_LVL_DBG = LogLevel::Trace;  // Debug builds

// Log level tags with colors
static constexpr ColorText TAG_CTX[] = {
    { "[TRCE]", ANSI::EX_Black },
    { "[DEBG]", ANSI::Cyan     },
    { "[INFO]", ANSI::Green    },
    { "[WARN]", ANSI::Yellow   },
    { "[ERRO]", ANSI::Red      },
    { "[FATL]", ANSI::BG_Red   },
};

// Scope tracing tags
static constexpr ColorText TRACE_IN_TAG  = {"--{", ANSI::EX_Green};
static constexpr ColorText TRACE_OUT_TAG = {"}--", ANSI::EX_Red};

// Testing tags
static constexpr ColorText TEST_TAG      = {"[TEST]", ANSI::Blue};
static constexpr ColorText PASS_TAG      = {"[PASS]", ANSI::Green};
static constexpr ColorText FAIL_TAG      = {"[FAIL]", ANSI::Red};

// Validation tags
static constexpr ColorText EXPECT_TAG    = {"[EXPC]", ANSI::Yellow};
static constexpr ColorText ASSERT_TAG    = {"[ASRT]", ANSI::Red};
static constexpr ColorText VERIFY_TAG    = {"[VRFY]", ANSI::BG_Red};
static constexpr ColorText PANIC_TAG     = {"[PANC]", ANSI::BG_Red};

// Formatting
static constexpr std::string_view TAB_TAG  = "    ";  // Indentation
static constexpr std::string_view TAG_TAG  = " : ";   // Separator

// === END MODIFIABLE VALUES ===

// ANSI reset code
static constexpr std::string_view COLOR_RESET = "\033[0m";

// Auto-detect build type
#ifdef NDEBUG
static constexpr LogLevel MIN_LEVEL = MIN_LVL_RLS; // Release
static constexpr bool IS_MODE_DEBUG = false;
#else
static constexpr LogLevel MIN_LEVEL = MIN_LVL_DBG; // Debug
static constexpr bool IS_MODE_DEBUG = true;
#endif

// Platform detection
#ifdef _WIN32
static constexpr bool IS_WINDOWS = true;
#else
static constexpr bool IS_WINDOWS = false;
#endif

// Process termination (throws in test mode, aborts in production)
#ifdef ZLOG_T
inline void killProcess() noexcept {} // Test mode - no termination
#else
[[noreturn]]
inline void killProcess() noexcept { std::abort(); } // Production
#endif

} // namespace config

// Output ColorText to stream (respects ENABLE_COLOR config)
inline std::ostream &operator<<(std::ostream &os, const ColorText &ct)
{
    if constexpr (!config::ENABLE_COLOR) return os << ct.TEXT;
    return os << "\033[" << static_cast<int>(ct.COLOR) << "m" << ct.TEXT << "\033[0m";
}

// Source code location tracking
struct SourceLoc {
    const bool        EMPTY;  //< True if default-constructed
    const std::string TEXT;   //< Formatted as "[FILE:LINE]"

    // Empty location
    SourceLoc() : EMPTY{true}, TEXT {""} {}

    // Create from file and line
    SourceLoc(std::string_view file, int line)
        : EMPTY{false}
        , TEXT{std::format("[{}:{}]", file, line)}
    {}

    // Output location in gray
    friend std::ostream &operator<<(std::ostream &os, const SourceLoc &sl)
    {
        return sl.EMPTY ? os : os << ColorText{sl.TEXT, ANSI::EX_Black};
    }
};

} // namespace zlog

// std::format support for ColorText
template <>
struct std::formatter<zlog::ColorText> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zlog::ColorText &color_text, std::format_context &ctx) const
    {
        return (!zlog::config::ENABLE_COLOR)
        ? std::format_to(ctx.out(), "{}", color_text.TEXT)
        : std::format_to(
            ctx.out(),
            "\033[{}m{}\033[0m",
            static_cast<int>(color_text.COLOR), color_text.TEXT
        );
    }
};

// std::format support for SourceLoc
template <>
struct std::formatter<zlog::SourceLoc> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zlog::SourceLoc &loc, std::format_context &ctx) const
    {
        return std::format_to(
            ctx.out(),
            "{}",
            zlog::ColorText{loc.TEXT, zlog::ANSI::EX_Black}
        );
    }
};

/// MACROS:

// Create `SourceLoc` for current location
#define _ZSL \
    { ::zlog::SourceLoc {__FILE__, __LINE__} }

#include <ctime>
#include <mutex>
#include <chrono>
#include <utility>
#include <iostream>

namespace zlog {

namespace internal {

// String class which supports regular and format strings
class ProString final {
public:
    const std::string TEXT;

    ProString() noexcept : TEXT {""} {}

    // Regular string constructor
    ProString(std::string_view text) noexcept : TEXT {text} {}

    // Format string constructor
    template <typename... Args>
    ProString(std::format_string<Args...> f_str, Args&&... args) noexcept
    : TEXT {std::format(f_str, std::forward<Args>(args)...)}
    {}

    // True is no text is provided
    [[nodiscard]]
    constexpr bool isEmpty() const noexcept { return TEXT == ""; }

    // Ostream support
    friend std::ostream &operator<<(std::ostream &os, const ProString &ps)
    {
        return os << ps.TEXT;
    }
};

// Thread-safe logging guard with mutex lock
struct LogGuard {
    std::scoped_lock<std::mutex> lock;  //< RAII mutex lock
    std::ostream&                os;    //< Reference to output stream

    LogGuard(std::mutex& mutex, std::ostream& os) : lock{mutex}, os{os} {}
};

// Returns thread-safe `LogGuard` for logging
[[nodiscard]]
inline LogGuard logStream(LogLevel level) noexcept
{
    static std::mutex s_log_mutex {};

    // Use cout for Trace/Debug/Info, cerr for Warn/Error/Fatal
    return LogGuard {
        s_log_mutex,
        static_cast<int>(level) < static_cast<int>(LogLevel::Warn)
        ? std::cout
        : std::cerr
    };
}

// Returns current timestamp as "[HH:MM:SS]" string
[[nodiscard]]
static inline std::string_view getTimestamp() noexcept
{
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm_struct{};

    thread_local char buf[sizeof("[HH:MM:SS]")] {};

#ifdef _WIN32
    localtime_s(&tm_struct, &t);
#else
    localtime_r(&t, &tm_struct);
#endif

    std::strftime(buf, sizeof(buf), "[%H:%M:%S]", &tm_struct);
    return std::string_view{buf, sizeof("[HH:MM:SS]")};
}

// Internal log function
inline void _log(LogLevel lvl, ProString msg) noexcept
{
    if (config::DISABLE_LOGGING || lvl < config::MIN_LEVEL) return;

    LogGuard log_gaurd = internal::logStream(lvl);
    log_gaurd.os << config::COLOR_RESET;

    if constexpr (config::ENABLE_TIMESTAMP)
    {
        log_gaurd.os
        << ColorText{internal::getTimestamp(), ANSI::EX_Black}
        << config::TAG_TAG;
    }

    log_gaurd.os
    << config::TAG_CTX[static_cast<int>(lvl)]
    << config::TAG_TAG << msg << "\n";
}

} // namespace internal

// Macro to generate logging functions for each level
#define _LOG_FN(FN_NAME, LOG_LVL)                     \
    inline void FN_NAME(internal::ProString message)  \
    { ::zlog::internal::_log(LOG_LVL, message); }     \

    // Generate logging functions for each level
    _LOG_FN(trace, LogLevel::Trace)
    _LOG_FN(dbg  , LogLevel::Debug)
    _LOG_FN(info , LogLevel::Info )
    _LOG_FN(warn , LogLevel::Warn )
    _LOG_FN(err  , LogLevel::Error)
    _LOG_FN(fatal, LogLevel::Fatal)

#undef _LOG_FN

} // namespace zlog

// std::format support for ProString
template <>
struct std::formatter<zlog::internal::ProString> {
    constexpr auto parse(std::format_parse_context &ctx) { return ctx.begin(); }

    auto format(const zlog::internal::ProString &ps, std::format_context &ctx) const
    {
        return std::format_to(ctx.out(), "{}", ps.TEXT);
    }
};

/// MACROS:

// Raw output with color reset
#define ZOUT  std::cout << "\n" << ::zlog::config::COLOR_RESET

// Standard logging
#define   ZDBG(...)  do { ::zlog::dbg  ({__VA_ARGS__}); } while (0)
#define  ZINFO(...)  do { ::zlog::info ({__VA_ARGS__}); } while (0)
#define  ZWARN(...)  do { ::zlog::warn ({__VA_ARGS__}); } while (0)
#define   ZERR(...)  do { ::zlog::err  ({__VA_ARGS__}); } while (0)
#define ZFATAL(...)  do { ::zlog::fatal({__VA_ARGS__}); } while (0)

// Conditional logging
#define   ZDBG_IF(COND, ...)  do { if (COND)   ZDBG(__VA_ARGS__); } while (0)
#define  ZINFO_IF(COND, ...)  do { if (COND)  ZINFO(__VA_ARGS__); } while (0)
#define  ZWARN_IF(COND, ...)  do { if (COND)  ZWARN(__VA_ARGS__); } while (0)
#define   ZERR_IF(COND, ...)  do { if (COND)   ZERR(__VA_ARGS__); } while (0)
#define ZFATAL_IF(COND, ...)  do { if (COND) ZFATAL(__VA_ARGS__); } while (0)

// Debug variable with name and value
#define ZVAR(VAR) do {                                     \
    ZDBG(                                                  \
        "{} = {}",                                         \
        ::zlog::ColorText { #VAR, ::zlog::ANSI::Magenta }, \
        (VAR)                                              \
    );                                                     \
} while (0)


namespace zlog {

#define _TAG_OS(TAG) \
    (TAG) << config::TAG_TAG

#define _TAG_COMM(TAG) \
    (TAG), config::TAG_TAG

#define _EXPR(EXPR) \
    ColorText{(EXPR), ANSI::Magenta}

#define _DESC(DESC) \
    ColorText{(DESC), ANSI::Bold}

namespace internal {

[[nodiscard]]
inline std::string _testFmt(
    const ColorText& tag,
    std::string_view expr,
    ProString& desc,
    const SourceLoc& loc
) noexcept {
    return desc.isEmpty()
    ? std::format(
        "{}{}{}{}{}",
        _TAG_COMM(tag),
        _TAG_COMM(loc),
        _EXPR(expr)
    )
    : std::format(
        "{}{}{}{}{}{}{}",
        _TAG_COMM(tag),
        _TAG_COMM(loc),
        _TAG_COMM(_EXPR(expr)),
        _DESC(desc.TEXT)
    );
}

} // namespace internal

/// Unit test assertion (always runs in tests)

inline void test(bool condition, std::string_view expr, internal::ProString desc) noexcept
{
    ZOUT
    << _TAG_OS(config::TEST_TAG)
    << _TAG_OS(condition ? config::PASS_TAG : config::FAIL_TAG)
    << _EXPR(expr)
    << (desc.isEmpty() ? "" : config::TAG_TAG)
    << _DESC(desc.TEXT);
}

/// expectation (non-fatal, always runs)
inline void expect(
    bool condition,
    std::string_view expr,
    internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZWARN(internal::_testFmt(config::EXPECT_TAG, expr, desc, loc));
}

/// assertion (fatal, only in debug builds)
inline void assert(
    bool condition,
    std::string_view expr,
    internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
#ifndef NDEBUG
    if constexpr (!config::IS_MODE_DEBUG) return; // only on debug
    if (condition) return;
    ZERR(internal::_testFmt(config::ASSERT_TAG, expr, desc, loc));
    config::killProcess();
#endif
}

/// verify (fatal, always)
inline void verify(
    bool condition,
    std::string_view expr,
    internal::ProString desc,
    SourceLoc loc = {}
) noexcept
{
    if (condition) return;
    ZFATAL(internal::_testFmt(config::VERIFY_TAG, expr, desc, loc));
    config::killProcess();
}

/// Panic with message (always fatal)
#ifndef ZLOG_T
[[noreturn]]
#endif
inline void panic(internal::ProString desc, SourceLoc loc = {}) noexcept
{
    if (desc.isEmpty())
        ZFATAL("{}{}{}", _TAG_COMM(config::PANIC_TAG), loc);
    else
        ZFATAL("{}{}{}{}{}", _TAG_COMM(config::PANIC_TAG), _TAG_COMM(loc), _DESC(desc.TEXT));

    config::killProcess();
}

#undef _TAG_OS
#undef _TAG_COMM
#undef _EXPR
#undef _DESC


} // namespace zlog

/// MACROS:

#define   ZTEST(COND, ...)  do { ::zlog::test  ((COND), (#COND), {__VA_ARGS__}      ); } while (0)
#define ZEXPECT(COND, ...)  do { ::zlog::expect((COND), (#COND), {__VA_ARGS__}, _ZSL); } while (0)
#define ZASSERT(COND, ...)  do { ::zlog::assert((COND), (#COND), {__VA_ARGS__}, _ZSL); } while (0)
#define ZVERIFY(COND, ...)  do { ::zlog::verify((COND), (#COND), {__VA_ARGS__}, _ZSL); } while (0)

#define    ZPANIC(...)        do {           ::zlog::panic({__VA_ARGS__}, _ZSL); } while (0)
#define ZPANIC_IF(COND, ...)  do { if (COND) ::zlog::panic({__VA_ARGS__}, _ZSL); } while (0)


namespace zlog {

enum class CautionCode : uint8_t {
    Todo,
    Deprecated,
    Optimization,
    Security,
    Performance,
};

enum class CriticalCode : uint8_t {
    Unreachable,
    Unimplemented,
    FixMe,
    Memory,
    ThreadSafety,
};

static constexpr std::string_view CAUTION_TAGS[] = {
    "[TODO]"        ,
    "[DEPRECATED]"  ,
    "[OPTIMIZATION]",
    "[SECURITY]"    ,
    "[PERFORMANCE]" ,
};

static constexpr std::string_view CRITICAL_TAGS[] = {
    "[UNREACHABLE]"   ,
    "[UNIMPLEMENTED]" ,
    "[FIX_ME]"        ,
    "[MEMORY]"        ,
    "[THREAD_SAFETY]" ,
};

inline void caution(
    CautionCode code,
    SourceLoc loc,
    internal::ProString msg
) noexcept {
    internal::_log(
        LogLevel::Warn,
        internal::ProString {
            "{}{}{}{}{}",
            ColorText{CAUTION_TAGS[static_cast<size_t>(code)], ANSI::Yellow},
            config::TAG_TAG,
            loc,
            config::TAG_TAG,
            msg
        }
    );
}

#ifndef ZLOG_T
[[noreturn]]
#endif
inline void critical(
    CriticalCode code,
    SourceLoc loc,
    internal::ProString msg
) noexcept {
    internal::_log(
        LogLevel::Fatal,
        {
            "{}{}{}{}{}",
            ColorText{CRITICAL_TAGS[static_cast<size_t>(code)], ANSI::BG_Red},
            config::TAG_TAG,
            loc,
            config::TAG_TAG,
            msg
        }
    );
#ifndef ZLOG_T
    config::killProcess();
#endif
}

} // namespace zlog

/// MACROS:

#define   ZON_DEBUG  if constexpr ( ::zlog::config::IS_MODE_DEBUG)
#define ZON_RELEASE  if constexpr (!::zlog::config::IS_MODE_DEBUG)

#define  ZCAUTION(code, ...)  do { ::zlog::caution (code, _ZSL, {__VA_ARGS__}); } while (0)
#define ZCRITICAL(code, ...)  do { ::zlog::critical(code, _ZSL, {__VA_ARGS__}); } while (0)

#define        ZTODO(...)  ZCAUTION(::zlog::CautionCode::Todo        , __VA_ARGS__)
#define  ZDEPRECATED(...)  ZCAUTION(::zlog::CautionCode::Deprecated  , __VA_ARGS__)
#define    ZOPTIMIZE(...)  ZCAUTION(::zlog::CautionCode::Optimization, __VA_ARGS__)
#define    ZSECURITY(...)  ZCAUTION(::zlog::CautionCode::Security    , __VA_ARGS__)
#define ZPERFORMANCE(...)  ZCAUTION(::zlog::CautionCode::Performance , __VA_ARGS__)

#define   ZUNREACHABLE(...)  ZCRITICAL(::zlog::CriticalCode::Unreachable  , __VA_ARGS__)
#define ZUNIMPLEMENTED(...)  ZCRITICAL(::zlog::CriticalCode::Unimplemented, __VA_ARGS__)
#define         ZFIXME(...)  ZCRITICAL(::zlog::CriticalCode::FixMe        , __VA_ARGS__)
#define        ZMEMORY(...)  ZCRITICAL(::zlog::CriticalCode::Memory       , __VA_ARGS__)
#define ZTHREAD_SAFETY(...)  ZCRITICAL(::zlog::CriticalCode::ThreadSafety , __VA_ARGS__)

#include <string>

namespace zlog {

// Uses RAII to log tracing messages of a scope
struct ScopeTracer {
private:
    const std::string STR_TEXT;  //< Owned tracing message

public:
    const ColorText TEXT;  //< Colored tracing message

    // Scope IN
    explicit ScopeTracer(internal::ProString text)
        : STR_TEXT{std::move(text.TEXT)}
        , TEXT{STR_TEXT, (config::ENABLE_TRACE_DULL) ? ANSI::EX_Black : ANSI::Reset}
    {
        internal::_log(
            LogLevel::Trace,
            {"{}{}{}", config::TRACE_IN_TAG, config::TAG_TAG, TEXT}
        );
    }

    // Scope OUT
    ~ScopeTracer()
    {
        internal::_log(
            LogLevel::Trace,
            {"{}{}{}", config::TRACE_OUT_TAG, config::TAG_TAG, TEXT}
        );
    }
};

} // namespace zlog

/// MACROS:

// For proper `ScopeTracer` construction
#define _ZTRC_ANON  ::zlog::ScopeTracer ZTRACE_tracer_##__COUNTER__

// Scope tracing
#define ZTRC         _ZTRC_ANON { {     "{}()",       __FUNCTION__} }
#define ZTRC_C(CLS)  _ZTRC_ANON { { "{}::{}()", #CLS, __FUNCTION__} }
#define ZTRC_S(...)  _ZTRC_ANON { {__VA_ARGS__} }
