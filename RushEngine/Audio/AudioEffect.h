#include "iostream"
using namespace std;
#include <vector>
#include "SDL_mixer.h"

class AudioEngine;

class AudioEffect
{
	Mix_Chunk* Element;
	bool WasNotPlaying;
	int Volume;
	vector<Mix_Chunk*> ForcedPlays;
	vector<int> StartTime;
	double Time;
	string Path;
	Mix_Chunk* GetElement()
	{
		Mix_Chunk* Return = NULL;
		int CurrentTime = SDL_GetTicks();
		for (unsigned int i = 0; i < ForcedPlays.size(); i++)
		{
			
			if ((CurrentTime-StartTime.at(i)) > int(Time*1000))
			{
				Return = ForcedPlays.at(i);
				StartTime.at(i) = SDL_GetTicks();
				break;
			}
		}
		if (Return == NULL)
		{
			Return = Mix_LoadWAV(Path.c_str());
			ForcedPlays.push_back(Return);
			StartTime.push_back(SDL_GetTicks());
		}
		return Return;
	}

	void ForcedPlay(int Loops = 0)
	{
		Mix_Chunk* NewChunk = GetElement();

		string Error = string(Mix_GetError()); //TODO: Remove this.


		Mix_PlayChannel(-1, NewChunk, Loops);
	}
public:
	AudioEffect(string PathToEffect, double Time)
	{
		Element = Mix_LoadWAV(PathToEffect.c_str());
		if (Element == NULL)
		{
			string Error = string(Mix_GetError());
		}
		this->Time = Time;
		WasNotPlaying = true;
		Volume = 64;
		Path = PathToEffect;
	}
	~AudioEffect()
	{
		Mix_FreeChunk(Element);
		for (unsigned int i = 0; i < ForcedPlays.size(); i++)
		{
			Mix_FreeChunk(ForcedPlays.at(i));
		}
	}
	void Play(int Loops = 0, bool ForcePlay = false)
	{
		if (WasNotPlaying)
		{
			Mix_VolumeChunk(Element, Volume);
			WasNotPlaying = false;
		}
		if (ForcePlay)
		{
			ForcedPlay(Loops);
		}
		else
		{
			Mix_PlayChannel(-1, Element, Loops);
		}
		
	}

	void SetVolume(int Volume)
	{
		this->Volume = Volume;
		Mix_VolumeChunk(Element, Volume);
	}
};