#pragma once

#include "engine/misc/render_call.hpp"

#include <vector>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

class RenderSystem final {
    friend core::App;

private:
    std::vector<std::reference_wrapper<misc::IRenderCall>> _render_calls;

    explicit RenderSystem() = default;
    ~RenderSystem() = default;

    void _update() noexcept;

public:
    RenderSystem(RenderSystem&&)                 = delete;
    RenderSystem(const RenderSystem&)            = delete;
    RenderSystem& operator=(RenderSystem&&)      = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    void reserve(size_t reserve) noexcept;
    void addRenderCall(const std::reference_wrapper<misc::IRenderCall> render_call) noexcept;
};

} // namespace dull::system
