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

} // namespace dull::misc
