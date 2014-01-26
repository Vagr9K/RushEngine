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
	Background(int LayerID = 0, bool AutoAdd = true)
		:BackgroundBASE(RushEngineInfo.Objects->getBackgroundManager(LayerID), RushEngineInfo.Eventing, AutoAdd)
	{

	}
};