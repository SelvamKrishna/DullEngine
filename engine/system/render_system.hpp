#pragma once

#include "engine/misc/render_call.hpp"

#include <vector>
#include <memory>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

class RenderSystem final {
    friend core::App;

private:
    std::vector<std::unique_ptr<misc::IRenderCall>> _render_calls;

    explicit RenderSystem() = default;
    ~RenderSystem() = default;

    void _update() noexcept;

public:
    constexpr RenderSystem(RenderSystem&&)                 noexcept = delete;
    constexpr RenderSystem(const RenderSystem&)            noexcept = delete;
    constexpr RenderSystem& operator=(RenderSystem&&)      noexcept = delete;
    constexpr RenderSystem& operator=(const RenderSystem&) noexcept = delete;

    void reserve(size_t reserve) noexcept;
    void addRenderCall(std::unique_ptr<misc::IRenderCall> render_call) noexcept;
};

} // namespace dull::system
