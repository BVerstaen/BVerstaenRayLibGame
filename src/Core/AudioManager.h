#pragma once
#include "raylib.h"
#include <unordered_map>

class AudioManager
{
public:
	enum class SoundList
	{
		PLAYERFLAP,
		PLAYERSHOOT,
		PLAYERDEATH,
		TARGETHIT,
	};

	enum class MusicList
	{
		TITLE,
		GAME,
		GAMEOVER,
	};


#pragma region Constructors / Desctructors / Movement

public:
	AudioManager();
	~AudioManager();
	AudioManager(const AudioManager& audioManager) = delete;
	AudioManager& operator=(const AudioManager& audioManager) = delete;
	AudioManager(AudioManager&& audioManager) noexcept = delete;
	AudioManager& operator=(AudioManager&& audioManager) noexcept = delete;

#pragma endregion

#pragma region Singleton
public:
	static AudioManager& Instance();
private:
	static AudioManager* s_instance;
#pragma endregion

public:
	void PlaySoundFromList(SoundList soundToPlay);
	void PlayMusicFromList(MusicList musicToPlay);
	void StopCurrentMusic();

	void UpdateMusic();

private:
	std::unordered_map<SoundList, Sound> m_soundList;
	std::unordered_map<MusicList, Music> m_musicList;
	Music m_currentMusic;
};