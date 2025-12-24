#include "engine/process/direct.hpp"

namespace dull::process {

void Direct::iStart       () { _start_fn();         }
void Direct::iProcess     () { _process_fn();       }
void Direct::iFixedProcess() { _fixed_process_fn(); }

void Direct::onStart       (ProcessFn fn) noexcept { _start_fn         = fn; }
void Direct::onProcess     (ProcessFn fn) noexcept { _process_fn       = fn; }
void Direct::onFixedProcess(ProcessFn fn) noexcept { _fixed_process_fn = fn; }

} // namespace dull::process
