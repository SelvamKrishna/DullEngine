#pragma once

#include "engine/core/handle.hpp"
#include "engine/util/vec2.hpp"

#include <vendor/zutil/zutil.hpp>

#include <string>

namespace dull::core {

// ---
// Application configuration
// ---
struct AppContext final {
    std::string title           = "Application";
    util::Vec2i windowDimension = {800, 600};
    bool        isVsyncEnabled  = false;
    bool        isResizeable    = false;
};

// ---
// Main application
// ---
struct App final : public zutil::Logger {
    friend Handle;

private:
    Handle _handle { {} };

public:
    App(App&&)                 = delete;
    App(const App&)            = delete;
    App& operator=(App&&)      = delete;
    App& operator=(const App&) = delete;

    explicit App(const AppContext& context = {});
    ~App() noexcept;

    [[nodiscard]] static   App& GetInstance() noexcept;
    [[nodiscard]] const Handle& GetHandle()   noexcept { return _handle; }

    void Run() noexcept;
    void Quit() noexcept;
};

} // namespace dull::core

/// MACROS:

#define DULL_HANDLE ::dull::core::App::GetInstance().GetHandle()
#define DULL_CTX    ::dull::core::App::GetInstance().GetHandle().context
