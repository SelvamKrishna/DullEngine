#pragma once

#include <zen/math/utility.hpp>
#include <zen/math/vec2.hpp>
#include <zen/math/vec3.hpp>
#include <zen/log/core.hpp>
#include <zen/log/tools.hpp>

#include <vendor/raylib.h>

#ifdef NDEBUG
#define ON_DBG if constexpr (false)
#define ON_RLS if constexpr (true)
#else
#define ON_DBG if constexpr (true)
#define ON_RLS if constexpr (false)
#endif

namespace dull::util {

    #define _RL_CONV_FN(_from, _to) \
        [[nodiscard]] inline constexpr _to CastRL(const _from& e)

    _RL_CONV_FN(zen::vec2, rl::Vector2) { return {e.x, e.y}; }
    _RL_CONV_FN(zen::vec3, rl::Vector3) { return {e.x, e.y, e.z}; }
    _RL_CONV_FN(rl::Vector2, zen::vec2) { return {e.x, e.y}; }
    _RL_CONV_FN(rl::Vector3, zen::vec3) { return {e.x, e.y, e.z}; }

    #undef _RL_CONV_FN

    inline void _RLTraceLogCallBack(int logLevel, const char* text, va_list args)
    {
        ON_RLS { (void)logLevel; (void)text; (void)args; return; }
        if (logLevel == rl::LOG_NONE) return;

        static const zen::log_tag TAG {"RL", zen::ansi_color::MAGENTA & zen::ansi_style::BOLD};

        std::string formatted;

        try {
            va_list args_copy;
            va_copy(args_copy, args);

            int size = vsnprintf(nullptr, 0, text, args_copy);
            va_end(args_copy);

            if (size > 0)
            {
                std::string buffer(size + 1, '\0');
                vsnprintf(buffer.data(), buffer.size(), text, args);
                formatted = buffer;
            }
        }
        catch (...) { formatted = "FAILED TO FORMAT RAYLIB LOG MESSAGE"; }

        if (logLevel == rl::LOG_FATAL)
        {
            zen::panic(formatted, &TAG);
            return;
        }

        TAG.log((logLevel <= rl::LOG_DEBUG)
            ? zen::log_lvl::DBG
            : static_cast<zen::log_lvl>(logLevel - rl::LOG_DEBUG)
        ) << zen::ansi_style::DIM << formatted;
    }

} // namespace dull::util

#define rl_cast ::dull::util::CastRL
