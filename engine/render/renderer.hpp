#pragma once

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::render {

    struct IRenderer {
        friend core::Engine;

    public:
        virtual ~IRenderer() = default;

    protected:
        virtual void IInit() {}
        virtual void IDraw() {}
        virtual void IShutdown() {}
    };

} // namespace dull::core
