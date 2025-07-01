#include "audio_system.hpp"

AudioSystem::~AudioSystem() {
  for (auto &[_, sound] : _sounds) UnloadSound(sound);
  for (auto &[_, music] : _musics) UnloadMusicStream(music);

  CloseAudioDevice();
}

void AudioSystem::_init() {
  InitAudioDevice();
}

void AudioSystem::_update() {
  if (_music) UpdateMusicStream(*_music);
}

void AudioSystem::loadSound(const std::string &sound_name, const std::string &file_path) {
  if (_sounds.find(sound_name) != _sounds.end()) return;
  _sounds[sound_name] = LoadSound(file_path.c_str());
}

void AudioSystem::playSound(const std::string &sound_name) {
  auto it = _sounds.find(sound_name);
  if (it != _sounds.end()) PlaySound(it->second);
}

void AudioSystem::unloadSound(const std::string &sound_name) {
  auto it = _sounds.find(sound_name);
  if (it == _sounds.end()) return;

  UnloadSound(it->second);
  _sounds.erase(it);
}

void AudioSystem::loadMusic(const std::string &music_name, const std::string &file_path) {
  if (_musics.find(music_name) != _musics.end()) return;
  _musics[music_name] = LoadMusicStream(file_path.c_str());
}

void AudioSystem::playMusic(const std::string &music_name) {
  auto it = _musics.find(music_name);
  if (it == _musics.end()) return;
  _music = &it->second;
  PlayMusicStream(*_music);
}

void AudioSystem::stopMusic() {
  if (_music) {
    StopMusicStream(*_music);
    _music = nullptr;
  }
}

void AudioSystem::unloadMusic(const std::string &music_name) {
  auto it = _musics.find(music_name);
  if (it != _musics.end()) {
    UnloadMusicStream(it->second);
    _musics.erase(it);
    if (_music == &it->second) _music = nullptr;
  }
}