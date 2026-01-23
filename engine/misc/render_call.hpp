#pragma once

// Forward Declaration
namespace dull::system { class RenderSystem; }

namespace dull::misc {

class IRenderCall {
  friend class system::RenderSystem;

private:
    const bool PERMANENT_CALL;

protected:
    virtual void iDraw() const = 0;

public:
    explicit IRenderCall() : PERMANENT_CALL {false} {}
    explicit IRenderCall(bool is_permanent) : PERMANENT_CALL {is_permanent} {}
    virtual ~IRenderCall() = default;
};

} // namespace dull::misc
