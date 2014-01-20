#include "iostream"
using namespace std;
#include "SDL_mixer.h"

class AudioEngine;

class AudioEffect
{
	Mix_Chunk* Element;
	bool WasNotPlaying;
	int Volume;
public:
	AudioEffect(string PathToEffect)
	{
		Element = Mix_LoadWAV(PathToEffect.c_str());
		WasNotPlaying = true;
		Volume = 64;
	}
	~AudioEffect()
	{
		Mix_FreeChunk(Element);
	}
	void Play(int Loops = 0)
	{
		if (WasNotPlaying)
		{
			Mix_VolumeChunk(Element, Volume);
			WasNotPlaying = false;
		}
		Mix_PlayChannel(-1, Element, Loops);
	}

	void SetVolume(int Volume)
	{
		this->Volume = Volume;
		Mix_VolumeChunk(Element, Volume);
	}
};