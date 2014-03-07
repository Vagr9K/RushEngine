#pragma once

#include "SDL.h"
#include "SDL_mixer.h"
#include "../Eventing/Eventing.h"
#include "AudioMusic.h"
#include "AudioEffect.h"

class AudioEngine
{
	EventingEngine* EventSys;
	Mix_Music* LastMusic;
public:
	AudioEngine(EventingEngine* EventSys)
	{
		this->EventSys = EventSys;
		Start(2);
		LastMusic = NULL;
	}
	~AudioEngine()
	{
		Stop();
	}
	bool Start(int ChanellNumber)
	{
		int Flags = MIX_INIT_FLAC | MIX_INIT_OGG | MIX_INIT_MP3;
		int Status = Mix_Init(Flags);

		if ((Status&Flags) != Flags)
		{
			EventSys->SystemEvents->AudioError("Audio can't be initialized : " + string(Mix_GetError()));
			return false;
		}
		else if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, ChanellNumber, 2048) < 0)
		{
			EventSys->SystemEvents->AudioError("Audio can't be initialized (OpenAudio) : " + string(Mix_GetError()));
			return false;
		}
		else
			return true;
	}
	void Stop()
	{
		Mix_CloseAudio();
		Mix_Quit();
	}

	void PlayEffect(Mix_Chunk* Effect)
	{

	}
	
	void PlayMusic(Mix_Music* Music, int Loops)
	{
		if (LastMusic != Music)
		{
			Mix_PlayMusic(Music, Loops);
			LastMusic = Music;
		}
	}

	void PauseMusic(Mix_Music* Music)
	{
		if (LastMusic == Music)
		{
			Mix_PauseMusic();
		}
	}
	void ResumeMusic(Mix_Music* Music)
	{
		if (LastMusic == Music)
		{
			Mix_ResumeMusic();
		}
	}
	void RestartMusic(Mix_Music* Music)
	{
		if (LastMusic == Music)
		{
			Mix_RewindMusic();
		}
	}
	void StopMusic(Mix_Music* Music)
	{
		if (LastMusic == Music)
		{
			Mix_HaltMusic();
		}
	}

	void SetMusicVolume(int Volume)
	{
		Mix_VolumeMusic(Volume);
	}

};