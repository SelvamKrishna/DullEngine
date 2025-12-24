#pragma once

#include "engine/misc/processor.hpp"

#include <functional>

namespace dull::process {

class Direct : private misc::IProcessor {
    friend class core::App;

private:
    constexpr static void noLogic() noexcept {}

    using ProcessFn = std::function<void()>;

    ProcessFn _start_fn         {noLogic};
    ProcessFn _process_fn       {noLogic};
    ProcessFn _fixed_process_fn {noLogic};

    void iStart() final;
    void iProcess() final;
    void iFixedProcess() final;

public:
    void onStart(ProcessFn fn) noexcept;
    void onProcess(ProcessFn fn) noexcept;
    void onFixedProcess(ProcessFn fn) noexcept;

};

} // namespace dull::process
