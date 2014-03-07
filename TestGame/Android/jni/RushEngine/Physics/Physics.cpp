#include "Physics.h"
#ifdef __WINDOWS__
#endif
PhysicsEngine::PhysicsEngine ()
        {
		
	}
void PhysicsEngine::AddWorld (b2World * NewWorld)
        {
#ifdef __WINDOWS__

		if (NewWorld==NULL)
		{
			throw "NewWorld is NULL.";
		}
#endif
		PhysicsWorlds.push_back(NewWorld);
	}
vector <b2World*> * PhysicsEngine::GetWorlds ()
        {
		return &PhysicsWorlds;
	}

