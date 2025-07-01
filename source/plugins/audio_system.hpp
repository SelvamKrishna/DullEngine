#pragma once

#include <string>
#include <unordered_map>

#include "../../vendor/raylib.h"

class AudioSystem {
private:
  friend class App;

private:
  std::unordered_map<std::string, Sound> _sounds;
  std::unordered_map<std::string, Music> _musics;
  Music *_music = nullptr;

private:
  AudioSystem() = default;
  ~AudioSystem();

  AudioSystem(const AudioSystem &) = delete;
  AudioSystem(AudioSystem &&) = delete;
  AudioSystem &operator=(const AudioSystem &) = delete;
  AudioSystem &operator=(AudioSystem &&) = delete;

  void _init();
  void _update();

public:
  [[nodiscard]] static inline AudioSystem &instance() noexcept {
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