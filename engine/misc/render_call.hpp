#pragma once

// Forward Declaration
namespace dull::system { class RenderSystem; }

namespace dull::misc {

struct RenderCallTag final {};

class IRenderCall {
  friend class system::RenderSystem;

protected:
    virtual void iDraw() const = 0;

public:
    virtual ~IRenderCall() = default;
};

class PermanentRenderCall {
private:
    IRenderCall& _render_call;
    bool _is_active {false};

public:
    explicit PermanentRenderCall(IRenderCall& render_call) noexcept;

    [[nodiscard]]
    bool isActive() const noexcept;
    void setActive(bool active_flag) noexcept;
};

} // namespace dull::misc
