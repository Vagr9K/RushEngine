#pragma once

#include "SDL.h"
#include "SDL_mixer.h"

#include "../Eventing/Eventing.h"

class Audio
{
	EventingEngine* EventSys;
public:
	Audio(EventingEngine* EventSys, int ChanellNumber)
	{
		this->EventSys = EventSys;
		Start(ChanellNumber);
	}
	bool Start(int ChanellNumber)
	{
		int Flags = MIX_INIT_FLAC | MIX_INIT_OGG;
		int Status = Mix_Init(Flags);

		if (Status&Flags != Flags)
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
};