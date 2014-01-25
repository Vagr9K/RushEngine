class GameEngine;
class EventingEngine;

class RuntimeInfo
{
public:
	GameEngine* GamePointer;
	EventingEngine* Eventing;
	ObjDBManager<ObjectElement>* ObjectsDatabase;
	ObjDBManager<EffectElement>* EffectDatabase;
	ObjDBManager<BackgroundElement>* BackgroundDatabase;
	ObjDBManager<InterfaceElement>* InterfaceDatabase;
	int DefaultObjManagerID;
	int DefaultInterfaceManagerID;
	int DefaultEffManagerID;
	int DefaultBackManagerID;
	RuntimeInfo()
	{
		GamePointer = NULL;
		Eventing = NULL;
		DefaultObjManagerID = 0;
		DefaultInterfaceManagerID = 0;
		DefaultEffManagerID = 0;
		DefaultBackManagerID = 0;
	}

};