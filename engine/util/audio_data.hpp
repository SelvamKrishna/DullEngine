#pragma once

#include "engine/misc/identification.hpp"

#include <vendor/raylib.h>

namespace dull::util {

struct SoundTag final {};

// =======================
// Wrapper for rl::Sound
// =======================
class Sound : public misc::Identified<SoundTag> {
private:
    rl::Sound _sound; //< Raylib sound

public:
    explicit Sound(std::string_view path);
    ~Sound() noexcept;

    void play() noexcept;
    void stop() noexcept;
    void pause() noexcept;
    void resume() noexcept;

    void setVolume(float volume) noexcept;
    void setPitch(float pitch) noexcept;
    void setPan(float pan) noexcept;

    [[nodiscard]] bool isPlaying() const noexcept;
};

struct MusicTag final {};

// =======================
// Wrapper for rl::Music
// =======================
class Music : public misc::Identified<MusicTag> {
private:
    rl::Music _music; //< Raylib music

public:
    explicit Music(std::string_view path);
    ~Music() noexcept;

    void play() noexcept;
    void stop() noexcept;
    void pause() noexcept;
    void resume() noexcept;
    void update() noexcept;
    void toggle() noexcept;

    void seek(float position) noexcept; //< Set music position

    void setLooping(bool loop) noexcept;
    void setVolume(float volume) noexcept;
    void setPitch(float pitch) noexcept;
    void setPan(float pan) noexcept;

    [[nodiscard]] bool isPlaying() const noexcept;
    [[nodiscard]] float getTimeLength() const noexcept;
    [[nodiscard]] float getTimePlayed() const noexcept;
};

} // namespace dull::util
