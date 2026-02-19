#include "engine/system/system_handle.hpp"

namespace dull::system {

static process::_VoidProcessor sVoidProcessor {};

SystemHandle::SystemHandle(const SystemContext& systemContext) noexcept
    : processorRef {systemContext.processorPtr == nullptr ? sVoidProcessor : *systemContext.processorPtr}
{}

} // namespace dull::system
