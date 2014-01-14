#pragma once

#include "EventManagers.h"
#include "SDL.h"
using namespace std;



class EventingEngine
{
public:
	SDL_Event GlobalEvent;
public:
	SystemEventing SystemEvents;
};

