#include "AudioManager.h"
#include <stdexcept>
#include "Random.h"
#include <string>

AudioManager::AudioManager()
{
	//Singleton
	if (s_instance)
		throw std::runtime_error("There can only be one random");
	s_instance = this;

	InitAudioDevice();

	//Load sounds
	m_soundList[SoundList::PLAYERFLAP] = LoadAllSoundsAtPath("Audio/PlayerFlap/PlayerFlap_", 4);
	m_soundList[SoundList::PLAYERSHOOT] = LoadAllSoundsAtPath("Audio/PlayerShoot/PlayerShoot_", 3);
	m_soundList[SoundList::PLAYERDEATH] = LoadAllSoundsAtPath("Audio/PlayerDeath_", 1);
	m_soundList[SoundList::TARGETHIT] = LoadAllSoundsAtPath("Audio/TargetHit/TargetHit_", 3);

	m_currentMusic = Music();
	m_musicList[MusicList::TITLE] = LoadMusicStream("Audio/Music_Title.mp3");
	m_musicList[MusicList::TITLE].looping = true;
	m_musicList[MusicList::GAME] = LoadMusicStream("Audio/Music_Game.mp3");
	m_musicList[MusicList::GAME].looping = true;
	m_musicList[MusicList::GAMEOVER] = LoadMusicStream("Audio/Music_Gameover.mp3");
	m_musicList[MusicList::GAMEOVER].looping = false;
}

AudioManager::~AudioManager()
{
	//Unload sounds (each sound of each sound poll)
	for (auto& sound : m_soundList)
	{
		for (Sound sfx : sound.second)
		{
			UnloadSound(sfx);
		}
	}

	//Unload musics
	for (auto& music : m_musicList)
	{
		UnloadMusicStream(music.second);
	}

	CloseAudioDevice();
}


#pragma region Singleton

AudioManager* AudioManager::s_instance = nullptr;
AudioManager& AudioManager::Instance()
{
	if (!s_instance)
		throw std::runtime_error("No random was created");

	return *s_instance;
}


void AudioManager::PlaySoundFromList(SoundList soundToPlay)
{
	auto it = m_soundList.find(soundToPlay);
	if (it == m_soundList.end())
	{
		TraceLog(LOG_ERROR, "Can't find music");
		return;
	}

	int indexToPlay = Random::Instance().RandomRange(0, (it->second.size() - 1));
	PlaySound(it->second[indexToPlay]);
}
void AudioManager::PlayMusicFromList(MusicList musicToPlay)
{
	auto it = m_musicList.find(musicToPlay);
	if (it == m_musicList.end())
	{
		TraceLog(LOG_ERROR, "Can't find music");
		return;
	}

	m_currentMusic = it->second;
	PlayMusicStream(m_currentMusic);
}

void AudioManager::StopCurrentMusic()
{	
	if (!IsMusicValid(m_currentMusic))
	{
		TraceLog(LOG_ERROR, "No music playing");
		return;
	}

	StopMusicStream(m_currentMusic);
}

void AudioManager::UpdateMusic()
{
	if (!IsMusicValid(m_currentMusic) || !IsMusicStreamPlaying(m_currentMusic))
		return;
	
	UpdateMusicStream(m_currentMusic);
}

std::vector<Sound> AudioManager::LoadAllSoundsAtPath(const std::string& soundWavPath, int numberIteration)
{
	std::vector<Sound> newSoundList;

	for (int i = 0; i < numberIteration; i++)
	{
		std::string sfxPath = soundWavPath + std::to_string(i) + ".wav";
		if (!FileExists(sfxPath.c_str()))
		{
			TraceLog(LOG_ERROR, "File [%s] is invalid", sfxPath.c_str());
			continue;
		}

		newSoundList.push_back(LoadSound(sfxPath.c_str()));
	}

	return newSoundList;
}
