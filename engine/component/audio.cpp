#include "engine/component/audio.hpp"

namespace dull::component {

Sound::Sound(util::Sound::ID id) noexcept : ID {id} {}

Sound::Sound(std::string_view path, float volume, float pitch, float pan) noexcept
: ID {DULL_CTX.audio_sys.loadSound(path)}
{
    util::Sound& sound = DULL_CTX.audio_sys.get(ID);
    sound.setVolume(volume);
    sound.setPitch(pitch);
    sound.setPan(pan);
}

Music::Music(util::Music::ID id) noexcept : ID {id} {}

Music::Music(std::string_view path, float volume, float pitch, float pan, bool looping) noexcept
: ID {DULL_CTX.audio_sys.loadMusic(path)}
{
    util::Music& music = DULL_CTX.audio_sys.get(ID);
    music.setVolume(volume);
    music.setPitch(pitch);
    music.setPan(pan);
    music.setLooping(looping);
}

} // namespace dull::component
