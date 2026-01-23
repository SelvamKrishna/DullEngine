#pragma once

// Forward Declaration
namespace dull::system { class RenderSystem; }

namespace dull::misc {

// =======================
// Interface for render calls
// =======================
class IRenderCall {
  friend class system::RenderSystem;

protected:
    virtual void iDraw() const = 0; //< Draw's the render call

public:
    virtual ~IRenderCall() = default;
};

class PermanentRenderCall {
private:
    IRenderCall& _render_call; //< Render call to be called permanently
    bool _is_active {false};   //< Whether the render call is active

public:
    explicit PermanentRenderCall(IRenderCall& render_call) noexcept;

    [[nodiscard]]
    bool isActive() const noexcept;
    void setActive(bool active_flag) noexcept;
};

} // namespace dull::misc
