#include "Physics.h"

PhysicsEngine::PhysicsEngine ()
        {
		
	}
void PhysicsEngine::AddWorld (b2World * NewWorld)
        {
		if (NewWorld==NULL)
		{
			throw "NewWorld is NULL.";
		}
		PhysicsWorlds.push_back(NewWorld);
	}
vector <b2World*> * PhysicsEngine::GetWorlds ()
        {
		return &PhysicsWorlds;
	}

