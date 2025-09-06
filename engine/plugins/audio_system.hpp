#pragma once

#include "engine/utils/misc.hpp"

#include "vendor/raylib.h"

#include <mutex>
#include <string>
#include <unordered_map>

/// System to handle audio in application
/// Provides API to handle Sound and Music data
/// TODO: Volume handling
/// UNTESTED:
class AudioSystem {
	friend class App;

private:
	mutable std::mutex _mutex;

	std::unordered_map<
		std::string, 
		Sound,
		Misc::TransparentStringHash,
		Misc::TransparentStringEqualTo
	> _sounds;

	std::unordered_map<
		std::string, 
		Music,
		Misc::TransparentStringHash,
		Misc::TransparentStringEqualTo
	> _musics;

	Music* _music = nullptr;

	explicit AudioSystem() = default;
	~AudioSystem();

	static void _init();
	void _update();

public:
	AudioSystem(const AudioSystem&) = delete;
	AudioSystem(AudioSystem&&) = delete;
	AudioSystem& operator=(const AudioSystem&) = delete;
	AudioSystem& operator=(AudioSystem&&) = delete;

	void loadSound(std::string_view sound_name, std::string_view file_path) noexcept;
	void playSound(std::string_view sound_name) noexcept;
	void unloadSound(std::string_view sound_name) noexcept;

	void loadMusic(std::string_view music_name, std::string_view file_path) noexcept;
	void playMusic(std::string_view music_name) noexcept;
	void stopMusic() noexcept;
	void unloadMusic(std::string_view music_name) noexcept;
};
