#pragma once

// Forward Declaration
namespace dull::core   { struct Engine; }
namespace dull::render { struct DrawHandle; }

namespace dull::core {

    struct IProcessor {
        friend core::Engine;

    protected:
        virtual ~IProcessor() = default;

        virtual void IInit() = 0;
        virtual void IUpdate() = 0;
        virtual void IFixedUpdate() = 0;
        virtual void IDraw(const render::DrawHandle&) = 0;
        virtual void IShutdown() = 0;
    };

    struct _VoidProcessor final : public IProcessor {
    private:
        void IInit() final {}
        void IUpdate() final {}
        void IFixedUpdate() final {}
        void IDraw(const render::DrawHandle&) final {}
        void IShutdown() final {}
    };

} // namespace dull::core
