#pragma once

#include "engine/misc/identification.hpp"

#include <vendor/raylib.h>

namespace dull::util {

struct SoundTag final {};

class Sound : public misc::Identified<SoundTag> {
private:
    rl::Sound _sound;

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

class Music : public misc::Identified<MusicTag> {
private:
    rl::Music _music;

public:
    explicit Music(std::string_view path);
    ~Music() noexcept;

    void play() noexcept;
    void stop() noexcept;
    void pause() noexcept;
    void resume() noexcept;
    void update() noexcept;

    void seek(float position) noexcept;

    void setVolume(float volume) noexcept;
    void setPitch(float pitch) noexcept;
    void setPan(float pan) noexcept;

    [[nodiscard]] bool isPlaying() const noexcept;
    [[nodiscard]] float getTimeLength() const noexcept;
    [[nodiscard]] float getTimePlayed() const noexcept;
};


} // namespace dull::util
