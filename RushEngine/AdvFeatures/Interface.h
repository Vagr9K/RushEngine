#include "../GameEngineRAW.h"

class Interface : public InterfaceBASE
{
public:
	Interface(ObjDBManager <InterfaceElement> * ManagerDB, EventingEngine * EventSystem)
		:InterfaceBASE(ManagerDB, EventSystem)
	{

	}
	Interface(ObjDBManager <InterfaceElement> * ManagerDB)
		:InterfaceBASE(ManagerDB, RushEngineInfo.Eventing)
	{

	}
	Interface(int LayerID = 0)
		:InterfaceBASE(RushEngineInfo.Objects->getInterfaceManager(LayerID), RushEngineInfo.Eventing)
	{

	}
};