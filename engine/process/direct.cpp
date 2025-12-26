#include "engine/process/direct.hpp"

namespace dull::process {

void Direct::iStart       () { _ctx.start_fn();         }
void Direct::iProcess     () { _ctx.process_fn();       }
void Direct::iFixedProcess() { _ctx.fixed_process_fn(); }

void Direct::onStart       (ProcessFn fn) noexcept { _ctx.start_fn         = fn; }
void Direct::onProcess     (ProcessFn fn) noexcept { _ctx.process_fn       = fn; }
void Direct::onFixedProcess(ProcessFn fn) noexcept { _ctx.fixed_process_fn = fn; }

void Direct::setProcessContext(const DirectContext& ctx) noexcept { _ctx = ctx; }

} // namespace dull::process
