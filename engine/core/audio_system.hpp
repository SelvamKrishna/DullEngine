#pragma once

// Forward Declaration
namespace dull::core { struct Engine; }

namespace dull::core {

    struct AudioSystem {
        friend core::Engine;

    private:
        explicit AudioSystem() = default;
        ~AudioSystem() = default;

    public:
        AudioSystem(AudioSystem&&)                 = delete;
        AudioSystem(const AudioSystem&)            = delete;
        AudioSystem& operator=(AudioSystem&&)      = delete;
        AudioSystem& operator=(const AudioSystem&) = delete;
    };

} // namespace dull::core
