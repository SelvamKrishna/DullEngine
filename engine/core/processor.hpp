#pragma once

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::core {

    struct IProcessor {
        friend core::Engine;

    protected:
        virtual ~IProcessor() = default;

        virtual void IInit       () {}
        virtual void IUpdate     () {}
        virtual void IFixedUpdate() {}
        virtual void IDraw       () {}
        virtual void IShutdown   () {}
    };

    struct _VoidProcessor final : public IProcessor {
    private:
        void IInit       () final {}
        void IUpdate     () final {}
        void IFixedUpdate() final {}
        void IDraw       () final {}
        void IShutdown   () final {}
    };

} // namespace dull::core
