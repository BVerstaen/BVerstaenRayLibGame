#include "AudioManager.h"
#include <stdexcept>

AudioManager::AudioManager()
{
	//Singleton
	if (s_instance)
		throw std::runtime_error("There can only be one random");
	s_instance = this;

	InitAudioDevice();

	//Load sounds


	m_currentMusic = Music();
	m_musicList[MusicList::GAMEOVER] = LoadMusicStream("Audio/Music_Gameover.mp3");
	m_musicList[MusicList::GAMEOVER].looping = false;
	m_musicList[MusicList::GAME] = LoadMusicStream("Audio/Music_Game.mp3");
	m_musicList[MusicList::GAME].looping = true;
	
}

AudioManager::~AudioManager()
{
	//Unload sounds
	for (auto& sound : m_soundList)
	{
		UnloadSound(sound.second);
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
	PlaySound(it->second);
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
