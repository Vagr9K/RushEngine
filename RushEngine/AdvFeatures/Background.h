#include "../GameEngineRAW.h"

class Background : public BackgroundBASE
{
public:
	Background(ObjDBManager <BackgroundElement> * DatabaseManager, EventingEngine * EventsEngine, bool AutoAdd = true)
	:BackgroundBASE(DatabaseManager, EventsEngine, AutoAdd)
	{

	}
	Background(ObjDBManager<BackgroundElement> * DatabaseManager, bool AutoAdd = true)
		:BackgroundBASE(DatabaseManager, RushEngineInfo.Eventing, AutoAdd)
	{

	}
	Background(bool AutoAdd = true)
		:BackgroundBASE(RushEngineInfo.BackgroundDatabase, RushEngineInfo.Eventing, AutoAdd)
	{

	}
};