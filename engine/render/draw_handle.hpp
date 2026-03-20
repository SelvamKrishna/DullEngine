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
    };

} // namespace dull::render
