#pragma once

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::system {

    struct RenderSystem {
        friend core::Engine;

    private:
        explicit RenderSystem() = default;
        ~RenderSystem() = default;

    public:
        RenderSystem(RenderSystem&&)                 = delete;
        RenderSystem(const RenderSystem&)            = delete;
        RenderSystem& operator=(RenderSystem&&)      = delete;
        RenderSystem& operator=(const RenderSystem&) = delete;
    };

} // namespace dull::system
