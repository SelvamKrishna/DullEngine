#pragma once

#include "engine/core/processor.hpp"

#include <functional>

namespace dull::util {

    struct DirectProcessor final : public dull::core::IProcessor {
    public:
        struct Context final {
            static constexpr void _FnVoid() noexcept {}

            std::function<void()> fnInit        = Context::_FnVoid;
            std::function<void()> fnUpdate      = Context::_FnVoid;
            std::function<void()> fnFixedUpdate = Context::_FnVoid;
            std::function<void()> fnDraw        = Context::_FnVoid;
            std::function<void()> fnShutdown    = Context::_FnVoid;
        };

    private:
        Context _processContext;

        void IInit()        final { this->_processContext.fnInit(); }
        void IUpdate()      final { this->_processContext.fnUpdate(); }
        void IFixedUpdate() final { this->_processContext.fnFixedUpdate(); }
        void IDraw()        final { this->_processContext.fnDraw(); }
        void IShutdown()    final { this->_processContext.fnShutdown(); }

    public:
        explicit DirectProcessor(const Context& processContext)
            : _processContext {std::move(processContext)}
        {}

        template<typename Fn>
        void SetFnInit(Fn&& fn) noexcept { this->_processContext.fnInit = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnUpdate(Fn&& fn) noexcept { this->_processContext.fnUpdate = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnFixedUpdate(Fn&& fn) noexcept { this->_processContext.fnFixedUpdate = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnDraw(Fn&& fn) noexcept { this->_processContext.fnDraw = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnShutdown(Fn&& fn) noexcept { this->_processContext.fnShutdown = std::forward<Fn>(fn); }
    };

} // namespace dull::util
