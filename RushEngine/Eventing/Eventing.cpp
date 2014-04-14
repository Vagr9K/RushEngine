
#include "Eventing.h"

EventingEngine::EventingEngine ()
        {
		SystemEvents = new SystemEventing();
		
		Input = new InputController(this);
		
		GlobalVariables = new GlobalVars();
	}

EventingEngine::~EventingEngine()
{
	delete SystemEvents;
	
	delete Input;
	
	delete GlobalVariables; 
}

