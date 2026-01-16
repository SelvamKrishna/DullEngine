#include "engine/system/audio_system.hpp"
#include "engine/config.hpp"

namespace dull::system {

void AudioSystem::_init() noexcept
{
    rl::InitAudioDevice();
    ZVERIFY(rl::IsAudioDeviceReady(), "Failed to initialize audio device");

    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Audio System initialized");
}

void AudioSystem::_update() noexcept
{
    const util::Music::ID MUSIC_ID = _current_music;
    if (!MUSIC_ID) return;

    util::Music& music = get(MUSIC_ID);
    if (!music.isPlaying()) return;

    music.update();
}

void AudioSystem::_quit() noexcept
{
    rl::CloseAudioDevice();
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Audio System shut down");
}

void AudioSystem::reserveSoundBuffer(size_t reserve) noexcept { _sound_buffer.reserve(reserve); }
void AudioSystem::reserveMusicBuffer(size_t reserve) noexcept { _music_buffer.reserve(reserve); }

[[nodiscard]]
util::Sound::ID AudioSystem::loadSound(std::string_view path) noexcept
{
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Loading sound: {}", path);
    return _sound_buffer.add(std::make_unique<util::Sound>(path));
}

void AudioSystem::unloadSound(util::Sound::ID id) noexcept
{
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Unloading sound: {}", id);
    _sound_buffer.remove(id);
}

[[nodiscard]]
util::Music::ID AudioSystem::loadMusic(std::string_view path) noexcept
{
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Loading music: {}", path);
    return _music_buffer.add(std::make_unique<util::Music>(path));
}

void AudioSystem::unloadMusic(util::Music::ID id) noexcept
{
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Unloading music: {}", id);
    _music_buffer.remove(id);
}

[[nodiscard]]
util::Sound& AudioSystem::get(util::Sound::ID sound_id) noexcept
{
    util::Sound* sound_ptr = _sound_buffer.find(sound_id);
    ZASSERT(sound_ptr != nullptr, "Sound ID `{}` not found", sound_id);
    return *sound_ptr;
}

[[nodiscard]]
util::Music& AudioSystem::get(util::Music::ID music_id) noexcept
{
    util::Music* music_ptr = _music_buffer.find(music_id);
    ZASSERT(music_ptr != nullptr, "Music ID `{}` not found", music_id);
    return *music_ptr;
}

[[nodiscard]]
util::Sound* AudioSystem::getSafe(util::Sound::ID sound_id) noexcept { return _sound_buffer.find(sound_id); }

[[nodiscard]]
util::Music* AudioSystem::getSafe(util::Music::ID music_id) noexcept { return _music_buffer.find(music_id); }

void AudioSystem::setMasterVolume(float volume) noexcept
{
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Master volume set to: {}", volume);
    rl::SetMasterVolume(volume);
}

float AudioSystem::getMasterVolume() const noexcept { return rl::GetMasterVolume(); }

void AudioSystem::setCurrentMusic(util::Music::ID music_id) noexcept
{
    if (_current_music == music_id) return;
    if constexpr (config::SHOULD_LOG_AUDIO_SYS) ZINFO("Current music set to: {}", music_id);
    _current_music = music_id;
}

} // namespace dull::system
