#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/util/audio_data.hpp"

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

// =======================
// System to own and manage audio data
// =======================
class AudioSystem final {
    friend core::App;
    friend util::Music;

private:
    misc::Buffer<util::Sound> _sound_buffer; //< Buffer for sounds
    misc::Buffer<util::Music> _music_buffer; //< Buffer for music

    util::Music::ID _current_music {0}; //< ID of the current music

    explicit AudioSystem() = default;
    ~AudioSystem() = default;

    void _init() noexcept;
    void _update() noexcept;
    void _quit() noexcept;

public:
    constexpr AudioSystem(AudioSystem&&)                 noexcept = delete;
    constexpr AudioSystem(const AudioSystem&)            noexcept = delete;
    constexpr AudioSystem& operator=(AudioSystem&&)      noexcept = delete;
    constexpr AudioSystem& operator=(const AudioSystem&) noexcept = delete;

    void reserveSoundBuffer(size_t reserve) noexcept;
    void reserveMusicBuffer(size_t reserve) noexcept;

    [[nodiscard]]
    util::Sound::ID loadSound(std::string_view path) noexcept;
    void unloadSound(util::Sound::ID sound_id) noexcept;

    [[nodiscard]]
    util::Music::ID loadMusic(std::string_view path) noexcept;
    void unloadMusic(util::Music::ID music_id) noexcept;

    [[nodiscard]]
    util::Sound& get(util::Sound::ID sound_id) noexcept;

    [[nodiscard]]
    util::Music& get(util::Music::ID music_id) noexcept;

    [[nodiscard]]
    util::Sound* getSafe(util::Sound::ID sound_id) noexcept;

    [[nodiscard]]
    util::Music* getSafe(util::Music::ID music_id) noexcept;

    void setMasterVolume(float volume) noexcept;
    float getMasterVolume() const noexcept;

    // Set the current music to play
    void setCurrentMusic(util::Music::ID music_id) noexcept;
};

} // namespace dull::system
