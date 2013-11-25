#include "Box2D/Box2D.h"
#include <vector>
using namespace std;

class PhysicsEngine
{
private:
	vector<b2World*> PhysicsWorlds;
public:
	PhysicsEngine()
	{
		
	}
	void AddWorld(b2World* NewWorld)
	{
		if (NewWorld==NULL)
		{
			throw "NewWorld is NULL.";
		}
		PhysicsWorlds.push_back(NewWorld);
	}

	vector<b2World*>* GetWorlds()
	{
		return &PhysicsWorlds;
	}


};