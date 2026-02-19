#pragma once

#include "engine/process/i_processor.hpp"
#include "engine/system/time_system.hpp"

namespace dull::system {

struct SystemContext final {
    process::IProcessor* processorPtr = nullptr;
};

struct SystemHandle final {
    system::TimeSystem timeSystem;
    process::IProcessor& processorRef;

    SystemHandle(const SystemContext& systemContext = {}) noexcept;
};

} // namespace dull::system
