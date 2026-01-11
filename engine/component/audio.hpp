#pragma once

#include "engine/core/app.hpp"
#include "engine/util/audio_data.hpp"

namespace dull::component {

// =======================
// Component for Sound Source
// =======================
class Sound final {
public:
    const util::Sound::ID ID;

    // This constructor takes an existing Sound ID.
    // Useful if you want to share the same sound data between multiple Sound Components.
    explicit Sound(util::Sound::ID id) noexcept;

    // This constructor load's a sound from a file.
    // If you create multiple Sound Components with the path, The sound data will be loaded multiple times.
    // This allows for different settings per Sound Component, but uses more memory.
    explicit Sound(
        std::string_view path,
        float volume = 1.0f,
        float pitch = 1.0f,
        float pan = 0.5f
    ) noexcept;

    util::Sound& operator*()  const noexcept { return DULL_CTX.audio_sys.get(ID); }
    util::Sound* operator->() const noexcept { return DULL_CTX.audio_sys.getSafe(ID); }
};

// =======================
// Component for Music Stream
// =======================
class Music final {
public:
    const util::Music::ID ID;

    // This constructor takes an existing Music ID.
    // Useful if you want to share the same music data between multiple Music Components.
    explicit Music(util::Music::ID id) noexcept;

    // This constructor load's a music from a file.
    // If you create multiple Music Components with the path, The music data will be loaded multiple times.
    // This allows for different settings per Music Component, but uses more memory.
    explicit Music(
        std::string_view path,
        float volume = 1.0f,
        float pitch = 1.0f,
        float pan = 0.5f,
        bool looping = false
    ) noexcept;

    util::Music& operator*()  const noexcept { return DULL_CTX.audio_sys.get(ID); }
    util::Music* operator->() const noexcept { return DULL_CTX.audio_sys.getSafe(ID); }
};

} // namespace dull::component
