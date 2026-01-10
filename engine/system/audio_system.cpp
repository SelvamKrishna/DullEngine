#include "engine/system/audio_system.hpp"

namespace dull::system {

AudioSystem::~AudioSystem() noexcept { rl::CloseAudioDevice(); }

void AudioSystem::_init() noexcept
{
    rl::InitAudioDevice();
    ZVERIFY(rl::IsAudioDeviceReady(), "Failed to initialize audio device");
}

void AudioSystem::_update() noexcept
{
    for (util::Music::ID& music : _music_queue) get(music).update();
}

void AudioSystem::_addMusicToQueue(util::Music::ID music_id) noexcept
{
    _music_queue.push_back(music_id);
}

void AudioSystem::reserveSoundBuffer(size_t reserve) noexcept { _sound_buffer.reserve(reserve); }
void AudioSystem::reserveMusicBuffer(size_t reserve) noexcept { _music_buffer.reserve(reserve); }

[[nodiscard]]
util::Sound::ID AudioSystem::loadSound(std::string_view path) noexcept
{
    return _sound_buffer.add(std::make_unique<util::Sound>(path));
}

void AudioSystem::unloadSound(util::Sound::ID id) noexcept { _sound_buffer.remove(id); }

[[nodiscard]]
util::Music::ID AudioSystem::loadMusic(std::string_view path) noexcept
{
    return _music_buffer.add(std::make_unique<util::Music>(path));
}

void AudioSystem::unloadMusic(util::Music::ID id) noexcept { _music_buffer.remove(id); }

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

void AudioSystem::setMasterVolume(float volume) noexcept { rl::SetMasterVolume(volume); }
float AudioSystem::getMasterVolume() const noexcept { return rl::GetMasterVolume(); }

} // namespace dull::system
