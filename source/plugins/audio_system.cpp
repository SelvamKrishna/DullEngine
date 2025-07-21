#include "audio_system.hpp"

#include "../utils/debug.hpp"

AudioSystem::~AudioSystem() {
    for (auto &[name, sound] : _sounds) {
        UnloadSound(sound);
    }

    for (auto &[name, music] : _musics) {
        UnloadMusicStream(music);
    }

    if (IsAudioDeviceReady()) {
        CloseAudioDevice();
    }
}

void AudioSystem::_init() {
    if (IsAudioDeviceReady()) {
        DULL_WARN("Audio system already initialized.");
        return;
    }

    InitAudioDevice();
}

void AudioSystem::_update() {
    if (!IsAudioDeviceReady()) [[unlikely]] {
        DULL_WARN("Trying to process audio system without initialization.");
        return;
    }

    if (_music == nullptr) {
        return;
    }

    UpdateMusicStream(*_music);
}

void AudioSystem::loadSound(const std::string &sound_name, const std::string &file_path) {
    if (!IsAudioDeviceReady()) {
        DULL_WARN("Unable to load '{}': Audio system not initialized.", sound_name);
        return;
    }

    if (_sounds.find(sound_name) != _sounds.end()) {
        DULL_WARN("Unable to load '{}': Name already exist.", sound_name);
        return;
    }

    Sound sound = LoadSound(file_path.c_str());
    if (!IsSoundValid(sound)) {
        DULL_WARN("Unable to load '{}': '{}' invalid.", sound_name, file_path);
        return;
    }

    _sounds[sound_name] = sound;
}

void AudioSystem::playSound(const std::string &sound_name) {
    if (!IsAudioDeviceReady()) {
        DULL_WARN("Unable to play '{}': Audio system not initialized.", sound_name);
        return;
    }

    auto it = _sounds.find(sound_name);
    if (it == _sounds.end()) {
        DULL_WARN("Unable to play '{}': Sound not found.", sound_name);
        return;
    }

    if (!IsSoundValid(it->second)) {
        DULL_WARN("Unable to play '{}': Sound invalid.", sound_name);
        return;
    }

    PlaySound(it->second);
}

void AudioSystem::unloadSound(const std::string &sound_name) {
    auto it = _sounds.find(sound_name);
    if (it == _sounds.end()) {
        DULL_WARN("Unable to unload '{}': Sound not found.", sound_name);
        return;
    }

    if (IsSoundPlaying(it->second)) {
        StopSound(it->second);
    }

    UnloadSound(it->second);
    _sounds.erase(it);
}

void AudioSystem::loadMusic(const std::string &music_name, const std::string &file_path) {
    if (!IsAudioDeviceReady()) {
        DULL_WARN("Unable to load '{}': Audio system not initialized.", music_name);
        return;
    }

    if (_musics.find(music_name) != _musics.end()) {
        DULL_WARN("Unable to load '{}': Name already exist.", music_name);
        return;
    }

    Music music = LoadMusicStream(file_path.c_str());
    if (IsMusicValid(music)) {
        DULL_WARN("Unable to load '{}': '{}' invalid.", music_name, file_path);
        return;
    }

    _musics[music_name] = music;
}

void AudioSystem::playMusic(const std::string &music_name) {
    if (!IsAudioDeviceReady()) {
        DULL_WARN("Unable to play '{}': Audio system not yet initialized.", music_name);
        return;
    }

    auto it = _musics.find(music_name);
    if (it == _musics.end()) {
        DULL_WARN("Unable to play '{}': Music not found.", music_name);
        return;
    }

    if (!IsMusicValid(it->second)) {
        DULL_WARN("Unable to play '{}': Music invalid.", music_name);
        return;
    }

    if (_music == &it->second && IsMusicStreamPlaying(*_music)) {
        return;
    }

    _music = &it->second;
    PlayMusicStream(*_music);
}

void AudioSystem::stopMusic() {
    if (_music == nullptr || !IsMusicStreamPlaying(*_music)) {
        return;
    }

    StopMusicStream(*_music);
    _music = nullptr;
}

void AudioSystem::unloadMusic(const std::string &music_name) {
    auto it = _musics.find(music_name);
    if (it == _musics.end()) {
        DULL_WARN("Unable to unload '{}': Music not found.", music_name);
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
}