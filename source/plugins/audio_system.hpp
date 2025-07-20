#pragma once

#include <string>
#include <unordered_map>

#include "../../vendor/raylib.h"

/// UNTESTED:
/// Class for managing sounds and music in the application.
/// A global singleton system which holds all audio resources.
class AudioSystem {
    friend class App;

private:
    std::unordered_map<std::string, Sound> _sounds; // One-shot audio effects
    std::unordered_map<std::string, Music> _musics; // Looping audio streams
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

    [[nodiscard]] static AudioSystem &instance() noexcept {
        static AudioSystem instance;
        return instance;
    }

    void loadSound(const std::string &sound_name, const std::string &file_path);
    void playSound(const std::string &sound_name);
    void unloadSound(const std::string &sound_name);

    void loadMusic(const std::string &music_name, const std::string &file_path);
    void playMusic(const std::string &music_name);
    void stopMusic();
    void unloadMusic(const std::string &music_name);
};