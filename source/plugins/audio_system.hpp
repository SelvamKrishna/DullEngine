#pragma once

#include "../../vendor/raylib.h"

#include <mutex>
#include <string>
#include <unordered_map>

/// UNTESTED:
/// TODO: Volume handling
class AudioSystem {
    friend class App;

private:
    mutable std::mutex _mutex;

    std::unordered_map<std::string, Sound> _sounds;
    std::unordered_map<std::string, Music> _musics;

    Music *_music = nullptr;

    AudioSystem() = default;
    ~AudioSystem();

    static void _init();
    void _update();

public:
    AudioSystem(const AudioSystem &) = delete;
    AudioSystem(AudioSystem &&) = delete;
    AudioSystem &operator=(const AudioSystem &) = delete;
    AudioSystem &operator=(AudioSystem &&) = delete;

    void loadSound(const std::string &sound_name, const std::string &file_path) noexcept;
    void playSound(const std::string &sound_name) noexcept;
    void unloadSound(const std::string &sound_name) noexcept;

    void loadMusic(const std::string &music_name, const std::string &file_path) noexcept;
    void playMusic(const std::string &music_name) noexcept;
    void stopMusic() noexcept;
    void unloadMusic(const std::string &music_name) noexcept;
};