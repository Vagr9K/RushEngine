class GameEngine;
class EventingEngine;
class PhysicsEngine;

class RuntimeInfo
{
public:
	GameEngine* GamePointer;
	EventingEngine* Eventing;
	PhysicsEngine* Physics;
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
		Physics = NULL;
		DefaultObjManagerID = 0;
		DefaultInterfaceManagerID = 0;
		DefaultEffManagerID = 0;
		DefaultBackManagerID = 0;
	}

};