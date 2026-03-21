#pragma once

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::render {

    struct DrawHandle {
        friend core::Engine;

    private:
        explicit DrawHandle();
        ~DrawHandle();

    public:
        DrawHandle(DrawHandle&&)                 = delete;
        DrawHandle(const DrawHandle&)            = delete;
        DrawHandle& operator=(DrawHandle&&)      = delete;
        DrawHandle& operator=(const DrawHandle&) = delete;

        void DrawShape();
    };

} // namespace dull::render
