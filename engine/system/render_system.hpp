#pragma once

#include "engine/misc/render_call.hpp"

#include <vector>

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

class RenderSystem final {
    friend core::App;

private:
    static std::vector<std::reference_wrapper<misc::IRenderCall>> s_one_frame_call;
    static std::vector<std::reference_wrapper<misc::IRenderCall>> s_permanent_call;

    explicit RenderSystem() = default;
    ~RenderSystem() = default;

    void _update() noexcept;
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
