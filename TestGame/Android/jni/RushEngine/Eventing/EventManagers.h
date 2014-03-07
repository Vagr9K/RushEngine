#pragma once

#include <fstream>
#include <ios>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <string>
using namespace std;

#include "SDL.h"
#include "EventComponents.h"

#if __cplusplus <= 199711L
#define to_string(Number) to_string(static_cast<long long>(Number))
#endif


class SystemEventing : public Events
{
public:
  void LogData (string Type, string Data, bool Throw);
  void GraphicsError (string Error);
  void OPSLog (string OPS);
  void ObjectsError (string Error);
  void AudioError(string Error);
};
class GlobalEventManager
{
	bool InLoop;
	bool UseLooping;
public:
  SDL_Event GlobalEvent;
public:
	GlobalEventManager()
	{
		InLoop = false;
		UseLooping = false;
	}
	void StartLoop()
	{
		InLoop = true;
		UseLooping = true;
		SDL_PollEvent(&GlobalEvent);
	}
	void EndLoop()
	{
		InLoop = false;
	}
  void Update ();
};
