#include "engine/core/app.hpp"
#include "engine/misc/render_call.hpp"

namespace dull::misc {

PermanentRenderCall::PermanentRenderCall(IRenderCall& render_call) noexcept
: _render_call {render_call} {}

[[nodiscard]]
bool PermanentRenderCall::isActive() const noexcept { return _is_active; }

void PermanentRenderCall::setActive(bool active_flag) noexcept
{
    if (_is_active == active_flag) [[unlikely]] return;
    _is_active = active_flag;

    (_is_active)
        ? DULL_CTX.render_sys.addPermanentCall(_render_call)
        : DULL_CTX.render_sys.removePermanentCall(_render_call)
    ;
}

} // namespace dull::misc
