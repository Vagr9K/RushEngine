#include "../GameEngineRAW.h"

class Object : public ObjectBASE
{
public:
	Object(bool SyncGraphics = true, bool AllowDraw = true) 
		: ObjectBASE(RushEngineInfo.Physics->GetWorlds()->at(RushEngineInfo.DefaultObjManagerID),
		RushEngineInfo.ObjectsDatabase, RushEngineInfo.Eventing, SyncGraphics, AllowDraw)
	{

	}
	Object(b2World* World, bool SyncGraphics = true, bool AllowDraw = true)
		: ObjectBASE(World, RushEngineInfo.ObjectsDatabase, RushEngineInfo.Eventing, SyncGraphics, AllowDraw)
	{

	}

	Object(b2World * ObjWorld, ObjDBManager <ObjectElement> * DatabaseManager, 
		EventingEngine * EventsEngine, bool SyncGraphics = true, bool AllowDraw = true) 
		: ObjectBASE(ObjWorld, DatabaseManager, EventsEngine, SyncGraphics, AllowDraw)
	{

	}
};