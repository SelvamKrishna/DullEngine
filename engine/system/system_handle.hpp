#pragma once

#include "engine/process/i_processor.hpp"
#include "engine/system/time_system.hpp"

#include <vendor/zutil/zutil.hpp>

namespace dull::system {

struct SystemContext final {
    process::IProcessor* processorPtr = nullptr;
};

struct SystemHandle final {
    system::TimeSystem timeSystem;
    process::IProcessor& processorRef;

    SystemHandle(const SystemContext& systemContext = {}) noexcept;

    template <typename ProcessorT>
        requires std::is_base_of_v<process::IProcessor, ProcessorT>
    [[nodiscard]] ProcessorT* GetProcessor() noexcept
    {
        return dynamic_cast<ProcessorT*>(&this->processorRef);
    }
};

} // namespace dull::system
