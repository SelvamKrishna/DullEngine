#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/util/audio_data.hpp"

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

class AudioSystem final {
    friend core::App;

private:
    misc::Buffer<util::Sound> _sound_buffer;
    misc::Buffer<util::Music> _music_buffer;

    explicit AudioSystem();
    ~AudioSystem();

public:
    constexpr AudioSystem(AudioSystem&&)                 noexcept = delete;
    constexpr AudioSystem(const AudioSystem&)            noexcept = delete;
    constexpr AudioSystem& operator=(AudioSystem&&)      noexcept = delete;
    constexpr AudioSystem& operator=(const AudioSystem&) noexcept = delete;

    void reserveSoundBuffer(size_t reserve) noexcept;
    void reserveMusicBuffer(size_t reserve) noexcept;

    [[nodiscard]]
    util::Sound::ID loadSound(std::string path) noexcept;
    void unloadSound(util::Sound::ID sound_id) noexcept;

    [[nodiscard]]
    util::Music::ID loadMusic(std::string path) noexcept;
    void unloadMusic(util::Music::ID music_id) noexcept;

    [[nodiscard]]
    util::Sound& get(util::Sound::ID sound_id) noexcept;

    [[nodiscard]]
    util::Music& get(util::Music::ID music_id) noexcept;
};

} // namespace dull::system
