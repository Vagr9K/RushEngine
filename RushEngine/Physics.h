#include <Box2D.h>
#include <vector>
using namespace std;

class Physics
{
private:
	vector<b2World*> PhysicsWorlds;
public:
	Physics()
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