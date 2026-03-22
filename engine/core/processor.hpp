#pragma once

#include <functional>

// Forward Declaration
namespace dull::util   { struct GlobalAccessor; }
namespace dull::core   { struct Engine; }
namespace dull::render { struct DrawHandle; }

namespace dull::core {

    struct IProcessor {
        friend core::Engine;

    protected:
        virtual ~IProcessor() = default;

        virtual void IInit() = 0;
        virtual void IUpdate(const util::GlobalAccessor&) = 0;
        virtual void IFixedUpdate(const util::GlobalAccessor&) = 0;
        virtual void IDraw(const render::DrawHandle&) = 0;
        virtual void IShutdown() = 0;
    };

    struct ProcessingFunctions final {
        static constexpr void _FnVoid() noexcept {}
        static constexpr void _FnDrawVoid(const render::DrawHandle&) noexcept {}
        static constexpr void _FnUpdateVoid(const util::GlobalAccessor&) noexcept {}

        std::function<void()> fnInit = ProcessingFunctions::_FnVoid;
        std::function<void(const util::GlobalAccessor&)> fnUpdate = ProcessingFunctions::_FnUpdateVoid;
        std::function<void(const util::GlobalAccessor&)> fnFixedUpdate = ProcessingFunctions::_FnUpdateVoid;
        std::function<void(const render::DrawHandle&)> fnDraw = ProcessingFunctions::_FnDrawVoid;
        std::function<void()> fnShutdown = ProcessingFunctions::_FnVoid;
    };

    struct DirectProcessor final : public dull::core::IProcessor {
    public:

    private:
        ProcessingFunctions _processFn;

        void IInit() final { this->_processFn.fnInit(); }

        void IUpdate(const util::GlobalAccessor& globalAccessor) final
        {
            this->_processFn.fnUpdate(globalAccessor);
        }

        void IFixedUpdate(const util::GlobalAccessor& globalAccessor) final
        {
            this->_processFn.fnFixedUpdate(globalAccessor);
        }

        void IDraw(const render::DrawHandle& drawHandle) final { this->_processFn.fnDraw(drawHandle); }

        void IShutdown() final { this->_processFn.fnShutdown(); }

    public:
        explicit DirectProcessor(const ProcessingFunctions& processContext)
            : _processFn {std::move(processContext)}
        {}

        template<typename Fn>
        void SetFnInit(Fn&& fn) noexcept { this->_processFn.fnInit = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnUpdate(Fn&& fn) noexcept { this->_processFn.fnUpdate = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnFixedUpdate(Fn&& fn) noexcept { this->_processFn.fnFixedUpdate = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnDraw(Fn&& fn) noexcept { this->_processFn.fnDraw = std::forward<Fn>(fn); }

        template<typename Fn>
        void SetFnShutdown(Fn&& fn) noexcept { this->_processFn.fnShutdown = std::forward<Fn>(fn); }
    };


} // namespace dull::core
