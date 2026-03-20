#pragma once

#include "engine/render/draw_handle.hpp"

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
        virtual void IDraw       (const render::DrawHandle&) {}
        virtual void IShutdown   () {}
    };

    struct _VoidProcessor final : public IProcessor {
    private:
        void IInit       () final {}
        void IUpdate     () final {}
        void IFixedUpdate() final {}
        void IDraw       (const render::DrawHandle&) final {}
        void IShutdown   () final {}
    };

} // namespace dull::core
