#pragma once

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::core {

    struct IRenderSystem {
        friend core::Engine;

    public:
        virtual ~IRenderSystem() = default;

    protected:
        virtual void IInit() {}
        virtual void IDraw() {}
        virtual void IShutdown() {}
    };

} // namespace dull::core
