#pragma once

#include "engine/misc/buffer.hpp"
#include "engine/util/audio_data.hpp"

// Forward Declaration
namespace dull::core { class App; }

namespace dull::system {

class AudioSystem final {
    friend core::App;
    friend util::Music;

private:
    misc::Buffer<util::Sound> _sound_buffer;
    misc::Buffer<util::Music> _music_buffer;

    explicit AudioSystem() = default;
    ~AudioSystem() noexcept;

    std::vector<util::Music::ID> _music_queue;

    void _init() noexcept;
    void _update() noexcept;
    void _addMusicToQueue(util::Music::ID music_id) noexcept;

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

    void setMasterVolume(float volume) noexcept;
    float getMasterVolume() const noexcept;
};

} // namespace dull::system
