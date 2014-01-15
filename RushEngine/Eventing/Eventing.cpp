
#include "Eventing.h"

EventingEngine::EventingEngine ()
        {
		SystemEvents = new SystemEventing();
		Input = new InputController(this);
	}

