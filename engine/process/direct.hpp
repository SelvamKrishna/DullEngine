#pragma once

#include "engine/misc/processor.hpp"

#include <functional>

namespace dull::process {

using ProcessFn = std::function<void()>;

// =======================
// All required processing functions
// =======================
struct DirectContext final {
private:
    constexpr static void noLogic() noexcept {}

public:
    ProcessFn start_fn         {noLogic};
    ProcessFn process_fn       {noLogic};
    ProcessFn fixed_process_fn {noLogic};
};

// =======================
// Simple processor
// =======================
class Direct : private misc::IProcessor {
    friend class core::App;

private:
    DirectContext _ctx;

    void iStart() final;
    void iProcess() final;
    void iFixedProcess() final;

public:
    void onStart(ProcessFn fn) noexcept;        //< Only change the Start fn
    void onProcess(ProcessFn fn) noexcept;      //< Only change the Process fn
    void onFixedProcess(ProcessFn fn) noexcept; //< Only change the FixedProcess fn

    // Sets all process functions
    void setProcessContext(const DirectContext& ctx) noexcept;
};

} // namespace dull::process
