#pragma once

// Forward Declaration
namespace dull::core { struct App; }

namespace dull::system {

    struct AudioSystem {
        friend core::App;

    private:
        explicit AudioSystem() = default;
        ~AudioSystem() = default;

    public:
        constexpr AudioSystem(AudioSystem&&)                 noexcept = delete;
        constexpr AudioSystem(const AudioSystem&)            noexcept = delete;
        constexpr AudioSystem& operator=(AudioSystem&&)      noexcept = delete;
        constexpr AudioSystem& operator=(const AudioSystem&) noexcept = delete;

    };

} // namespace dull::system
