#include "audio_system.hpp"

#include "../utils/debug.hpp"
#include <format>
#include <mutex>

AudioSystem::~AudioSystem() {
    stopMusic();

    for (auto &[_, sound] : _sounds) {
        UnloadSound(sound);
    }

    for (auto &[_, music] : _musics) {
        UnloadMusicStream(music);
    }

    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }
}

void AudioSystem::_init() {
    if (IsAudioDeviceReady()) {
        ErrorCtx("Audio system initilalization").failFallback("Already initialized");
        return;
    }

    InitAudioDevice();
}

void AudioSystem::_update() {
    if (!IsAudioDeviceReady()) [[unlikely]] {
        ErrorCtx("Audio system update").failFallback("Not initialized");
        return;
    }

    if (_music == nullptr) {
        return;
    }

    UpdateMusicStream(*_music);
}

void AudioSystem::loadSound(const std::string &sound_name, const std::string &file_path) noexcept {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Load sound '{}'", sound_name));

    if (!IsAudioDeviceReady()) {
        err.failFallback("Audio system not initialized");
        return;
    }

    if (_sounds.find(sound_name) != _sounds.end()) {
        err.failFallback("Name already exist");
        return;
    }

    Sound sound = LoadSound(file_path.c_str());
    if (!IsSoundValid(sound)) {
        err.failFallback(std::format("File path '{}' invalid", file_path));
        return;
    }

    _sounds[sound_name] = sound;
    DULL_INFO("Sound loaded successfully: {}", sound_name);
}

void AudioSystem::playSound(const std::string &sound_name) noexcept {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Play sound '{}'", sound_name));

    if (!IsAudioDeviceReady()) {
        err.failFallback("Audio system not initialized");
        return;
    }

    auto it = _sounds.find(sound_name);
    if (it == _sounds.end()) {
        err.failFallback("Not found");
        return;
    }

    if (!IsSoundValid(it->second)) {
        err.failFallback("Invalid sound");
        return;
    }

    PlaySound(it->second);
}

void AudioSystem::unloadSound(const std::string &sound_name) noexcept {
    std::lock_guard<std::mutex> lock(_mutex);

    auto it = _sounds.find(sound_name);
    if (it == _sounds.end()) {
        ErrorCtx(std::format("Unload sound '{}'", sound_name)).failFallback("Not found");
        return;
    }

    if (IsSoundPlaying(it->second)) {
        StopSound(it->second);
    }

    UnloadSound(it->second);
    _sounds.erase(it);
    DULL_INFO("Sound unloaded successfully: {}", sound_name);
}

void AudioSystem::loadMusic(const std::string &music_name, const std::string &file_path) noexcept {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Load music '{}'", music_name));

    if (!IsAudioDeviceReady()) {
        err.failFallback("Audio system not initialized");
        return;
    }

    if (_musics.find(music_name) != _musics.end()) {
        err.failFallback("Name already exist");
        return;
    }

    Music music = LoadMusicStream(file_path.c_str());
    if (IsMusicValid(music)) {
        err.failFallback(std::format("File path '{}' invalid", file_path));
        return;
    }

    _musics[music_name] = music;
    DULL_INFO("Music loaded successfully: {}", music_name);
}

void AudioSystem::playMusic(const std::string &music_name) noexcept {
    std::lock_guard<std::mutex> lock(_mutex);
    ErrorCtx err(std::format("Play music '{}'", music_name));

    if (!IsAudioDeviceReady()) {
        err.failFallback("Audio system not initialized");
        return;
    }

    auto it = _musics.find(music_name);
    if (it == _musics.end()) {
        err.failFallback("Not found");
        return;
    }

    if (!IsMusicValid(it->second)) {
        err.failFallback("Invalid music");
        return;
    }

    _music = &it->second;

    if (IsMusicStreamPlaying(*_music)) {
        return;
    }

    PlayMusicStream(*_music);
}

void AudioSystem::stopMusic() noexcept {
    std::lock_guard<std::mutex> lock(_mutex);

    if (_music == nullptr || !IsMusicStreamPlaying(*_music)) {
        return;
    }

    StopMusicStream(*_music);
    _music = nullptr;
}

void AudioSystem::unloadMusic(const std::string &music_name) noexcept {
    std::lock_guard<std::mutex> lock(_mutex);

    auto it = _musics.find(music_name);
    if (it == _musics.end()) {
        ErrorCtx(std::format("Unload music {}", music_name)).failFallback("Not found");
        return;
    }

    if (_music == &it->second) {
        if (IsMusicStreamPlaying(*_music)) {
            StopMusicStream(*_music);
        }

        _music = nullptr;
    }

    UnloadMusicStream(it->second);
    _musics.erase(it);
    DULL_INFO("Music unloaded successfully: {}", music_name);
}