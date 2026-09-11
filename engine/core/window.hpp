#pragma once

#include "engine/util/adapter.hpp"

#include <string>
#include <string_view>

#include <zen/math/vec2.hpp>
#include <vendor/raylib.h>

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::core {

    struct Window {
        friend core::Engine;

    private:
        Window() = default;
        ~Window() = default;

    public:
        using MonitorID = int32_t;
        using Dimension = std::array<uint32_t, 2>;

        Window(Window&&)                 = delete;
        Window(const Window&)            = delete;
        Window& operator=(Window&&)      = delete;
        Window& operator=(const Window&) = delete;

        [[nodiscard]] inline constexpr bool IsFullscreen() const noexcept { return rl::IsWindowFullscreen(); }
        [[nodiscard]] inline constexpr bool IsHidden()     const noexcept { return rl::IsWindowHidden(); }
        [[nodiscard]] inline constexpr bool IsMinimized()  const noexcept { return rl::IsWindowMinimized(); }
        [[nodiscard]] inline constexpr bool IsMaximized()  const noexcept { return rl::IsWindowMaximized(); }
        [[nodiscard]] inline constexpr bool IsFocused()    const noexcept { return rl::IsWindowFocused(); }
        [[nodiscard]] inline constexpr bool IsResized()    const noexcept { return rl::IsWindowResized(); }

        inline constexpr void ToggleFullscreen()         noexcept { rl::ToggleFullscreen(); }
        inline constexpr void ToggleBorderlessWindowed() noexcept { rl::ToggleBorderlessWindowed(); }
        inline constexpr void Maximize()                 noexcept { rl::MaximizeWindow(); }
        inline constexpr void Minimize()                 noexcept { rl::MinimizeWindow(); }

        /// TODO: void SetIcon(Image image);
        void SetTitle(std::string_view title) noexcept { rl::SetWindowTitle(title.data()); }
        void SetPosition(Dimension position)  noexcept { rl::SetWindowPosition(position[0], position[1]); }
        void SetMinSize(Dimension size)       noexcept { rl::SetWindowMinSize(size[0], size[1]); }
        void SetMaxSize(Dimension size)       noexcept { rl::SetWindowMaxSize(size[0], size[1]); }
        void SetSize(Dimension size)          noexcept { rl::SetWindowSize(size[0], size[1]); }
        void SetOpacity(float opacity)        noexcept { rl::SetWindowOpacity(opacity); }
        void SetFocused()                     noexcept { rl::SetWindowFocused(); }
        void SetMonitor(MonitorID monitor)    noexcept { rl::SetWindowMonitor(monitor); }

        [[nodiscard]] Dimension GetSize() const noexcept
        {
            return {
                static_cast<uint32_t>(rl::GetScreenWidth()),
                static_cast<uint32_t>(rl::GetScreenHeight())
            };
        }

        [[nodiscard]] Dimension GetRenderSize() const noexcept
        {
            return {
                static_cast<uint32_t>(rl::GetRenderWidth()),
                static_cast<uint32_t>(rl::GetRenderHeight())
            };
        }

        [[nodiscard]] zen::vec2 GetPosition() const noexcept { return rl_cast(rl::GetWindowPosition()); }
        [[nodiscard]] zen::vec2 GetScaleDPI() const noexcept { return rl_cast(rl::GetWindowScaleDPI()); }

        [[nodiscard]] uint32_t GetMonitorCount() const noexcept { return rl::GetMonitorCount(); }
        [[nodiscard]] uint32_t GetCurrentMonitor() const noexcept { return rl::GetCurrentMonitor(); }
        [[nodiscard]] zen::vec2 GetMonitorPosition(MonitorID monitor) const noexcept { return rl_cast(rl::GetMonitorPosition(monitor)); }
        [[nodiscard]] uint32_t GetMonitorRefreshRate(MonitorID monitor) const noexcept { return rl::GetMonitorRefreshRate(monitor); }
        [[nodiscard]] std::string GetMonitorName(MonitorID monitor) const noexcept { return rl::GetMonitorName(monitor); }

        [[nodiscard]] Dimension GetMonitorSize(MonitorID monitor) const noexcept
        {
            return {
                static_cast<uint32_t>(rl::GetMonitorWidth(monitor)),
                static_cast<uint32_t>(rl::GetMonitorHeight(monitor))
            };
        }

        [[nodiscard]] Dimension GetMonitorPhysicalSize(MonitorID monitor) const noexcept
        {
            return {
                static_cast<uint32_t>(rl::GetMonitorPhysicalWidth(monitor)),
                static_cast<uint32_t>(rl::GetMonitorPhysicalHeight(monitor))
            };
        }
    };

} // namespace dull::core
