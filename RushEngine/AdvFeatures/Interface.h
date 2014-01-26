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
	Interface()
		:InterfaceBASE(RushEngineInfo.InterfaceDatabase, RushEngineInfo.Eventing)
	{

	}

};