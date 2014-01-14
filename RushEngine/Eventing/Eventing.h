#pragma once

#include "EventManagers.h"
#include "Input.h"
using namespace std;



class EventingEngine : public GlobalEventManager
{
public:

public:
	SystemEventing* SystemEvents;
	InputController* Input;
	EventingEngine()
	{
		SystemEvents = new SystemEventing();
		Input = new InputController(this);
	}
	
};

