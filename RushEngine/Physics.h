#include <Box2D.h>
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
		PhysicsWorlds.push_back(NewWorld);
	}

	vector<b2World*> GetWorlds()
	{
		return PhysicsWorlds;
	}


};