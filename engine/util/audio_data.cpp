#include "engine/core/app.hpp"
#include "engine/util/audio_data.hpp"

#include <algorithm>

namespace dull::util {

Sound::Sound(std::string_view path)
: misc::Identified<SoundTag> {std::string{path}}
, _sound {rl::LoadSound(path.data())}
{
    ZASSERT(rl::IsSoundValid(_sound), "Sound '{}' failed to load.", getName());
}

Sound::~Sound() noexcept { rl::UnloadSound(_sound); }

void Sound::play()   noexcept { rl::PlaySound(_sound); }
void Sound::stop()   noexcept { rl::StopSound(_sound); }
void Sound::pause()  noexcept { rl::PauseSound(_sound); }
void Sound::resume() noexcept { rl::ResumeSound(_sound); }

void Sound::setVolume(float volume) noexcept { rl::SetSoundVolume(_sound, std::clamp(volume, 0.0f, 1.0f)); }
void Sound::setPitch(float pitch)   noexcept { rl::SetSoundPitch(_sound, pitch); }
void Sound::setPan(float pan)       noexcept { rl::SetSoundPan(_sound, std::clamp(pan, 0.0f, 1.0f)); }

[[nodiscard]]
bool Sound::isPlaying() const noexcept { return rl::IsSoundPlaying(_sound); }

Music::Music(std::string_view path)
: misc::Identified<MusicTag> {std::string{path}}
, _music {rl::LoadMusicStream(path.data())}
{
    ZASSERT(rl::IsMusicValid(_music), "Music '{}' failed to load.", getName());
}

Music::~Music() noexcept { rl::UnloadMusicStream(_music); }

void Music::play() noexcept
{
    if (isPlaying()) return;
    rl::PlayMusicStream(_music);
    DULL_CTX.audio_sys.setCurrentMusic(getID());
}

void Music::stop()   noexcept { rl::StopMusicStream(_music); }
void Music::pause()  noexcept { rl::PauseMusicStream(_music); }
void Music::resume() noexcept { rl::ResumeMusicStream(_music); }
void Music::update() noexcept { rl::UpdateMusicStream(_music); }
void Music::toggle() noexcept { isPlaying() ? pause() : play(); }

void Music::seek(float position) noexcept { rl::SeekMusicStream(_music, position); }

void Music::setLooping(bool loop)   noexcept { _music.looping = loop; }
void Music::setVolume(float volume) noexcept { rl::SetMusicVolume(_music, std::clamp(volume, 0.0f, 1.0f)); }
void Music::setPitch(float pitch)   noexcept { rl::SetMusicPitch(_music, pitch); }
void Music::setPan(float pan)       noexcept { rl::SetMusicPan(_music, std::clamp(pan, 0.0f, 1.0f)); }

[[nodiscard]] bool Music::isPlaying()      const noexcept { return rl::IsMusicStreamPlaying(_music); }
[[nodiscard]] float Music::getTimeLength() const noexcept { return rl::GetMusicTimeLength(_music); }
[[nodiscard]] float Music::getTimePlayed() const noexcept { return rl::GetMusicTimePlayed(_music); }

} // namespace dull::util
