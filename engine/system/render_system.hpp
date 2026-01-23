#pragma once

#include "engine/misc/render_call.hpp"

#include <vector>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

// =======================
// System to manage render calls
// =======================
class RenderSystem final {
    friend core::App;

private:
    static std::vector<std::reference_wrapper<misc::IRenderCall>> s_one_frame_call; //< Render calls that are only called once
    static std::vector<std::reference_wrapper<misc::IRenderCall>> s_permanent_call; //< Permanent render calls

    explicit RenderSystem() = default;
    ~RenderSystem() = default;

    // Draw's all render calls & clear's one frame calls
    void _update() noexcept;

    // Clear's all render calls
    void _quit() noexcept;

public:
    RenderSystem(RenderSystem&&)                 = delete;
    RenderSystem(const RenderSystem&)            = delete;
    RenderSystem& operator=(RenderSystem&&)      = delete;
    RenderSystem& operator=(const RenderSystem&) = delete;

    void reserveOneFrameBuffer(size_t reserve) noexcept;
    void reservePermanentBuffer(size_t reserve) noexcept;

    void addPermanentCall(misc::IRenderCall& render_call) noexcept;
    void removePermanentCall(misc::IRenderCall& render_call) noexcept;

    void addOneFrameCall(misc::IRenderCall& render_call) noexcept;
};

} // namespace dull::system
