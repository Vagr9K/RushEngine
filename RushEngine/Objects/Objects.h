#pragma once

#include <vector>
#include "Object.h"
#include "Effects.h"
#include "Interface.h"

typedef vector<ObjDBManager<ObjectElement>*> ObjectElementManagers;
typedef vector<ObjectElement*> ObjectElementData;

typedef vector<ObjDBManager<EffectElement>*>  EffectElementManagers;
typedef vector<EffectElement*> EffectElementData;

typedef vector<ObjDBManager<InterfaceElement>*> InterfaceElementManagers;
typedef vector<InterfaceElement*> InterfaceElementData;

class ObjectsEngine
{

	int InterfaceLayerCount;
	int WorldCount;
	int BackgroundLayerCount;
	int EffectLayerCount;



public:
	int OptObjCount;

private:
	ObjectElementManagers ObjectsManagers;
	ObjectElementData** ObjectsData;

	EffectElementManagers EffectManagers;
	EffectElementData** EffectData;

	InterfaceElementManagers InterfaceManagers;
	InterfaceElementData** InterfaceData;

private:
	void InitOldCpp()
	{
		OptObjCount = 0;
	}

	void InitObjects(int WorldCount)
	{
		if (WorldCount != 0)
		{
			ObjectsData = new ObjectElementData*[WorldCount];
		}
		else
		{
			ObjectsData = NULL;
		}
		for (int i = 0; i < WorldCount; i++)
		{
			ObjectsData[i] = new ObjectElementData;
			ObjectsManagers.push_back(new ObjDBManager<ObjectElement>(ObjectsData[i]));
		}

	}

	
	void InitEffect(int WorldCount)
	{
		if (WorldCount != 0)
		{
			EffectData = new EffectElementData*[WorldCount];
		}
		else
		{
			EffectData = NULL;
		}
		for (int i = 0; i < WorldCount; i++)
		{
			EffectData[i] = new EffectElementData;
			EffectManagers.push_back(new ObjDBManager<EffectElement>(EffectData[i]));
		}
	}

	void InitInterface(int InterfaceCount)
	{
		if (InterfaceCount != 0)
		{
			InterfaceData = new InterfaceElementData*[InterfaceCount];
		}
		else
		{
			InterfaceData = NULL;
		}
		for (int i = 0; i < InterfaceCount; i++)
		{
			InterfaceData[i] = new InterfaceElementData;
			InterfaceManagers.push_back(new ObjDBManager<InterfaceElement>(InterfaceData[i]));
		}
	}

	void DefContructor(int InterfaceLayerCount, int EffectLayerCount, int WorldCount, int BackgroundLayerCount)
	{
		InitOldCpp();
		this->InterfaceLayerCount = InterfaceLayerCount;
		this->WorldCount = WorldCount;
		this->BackgroundLayerCount = BackgroundLayerCount;
		this->EffectLayerCount = EffectLayerCount;

		/*New API*/
		InitObjects(WorldCount);
		InitEffect(EffectLayerCount);
		InitInterface(InterfaceLayerCount);

		/*New API END*/
	}
public:
	ObjectsEngine(int InterfaceLayerCount,int EffectsLayerCount ,int WorldCount, int BackgroundLayerCount)
	{
		DefContructor(InterfaceLayerCount, EffectsLayerCount, WorldCount, BackgroundLayerCount);

	}
	ObjectsEngine(int InterfaceLayerCount, int EffectsLayerCount, int WorldCount, int BackgroundLayerCount, int OptimalObjectsCount)
	{
		DefContructor(InterfaceLayerCount, EffectsLayerCount, WorldCount, BackgroundLayerCount);
		this->OptObjCount = OptimalObjectsCount;
	}


	int GetCount()
	{
		return InterfaceLayerCount + EffectLayerCount + WorldCount + BackgroundLayerCount;
	}

	int GetEffectLCount()
	{
		return EffectLayerCount;
	}
	int GetWorldLCount()
	{
		return WorldCount;
	}
	int GetInterfaceLCount()
	{
		return InterfaceLayerCount;
	}
	int GetBackgroundLCount()
	{
		return BackgroundLayerCount;
	}

	/*NEW API*/
	ObjDBManager<ObjectElement>* getObjectManager(int ID = 0)
	{
		return ObjectsManagers.at(ID);
	}
	ObjectElementData* getObjectsLayer(int ID = 0)
	{
		return ObjectsData[ID];
	}

	ObjDBManager<EffectElement>* getEffectManager(int ID = 0)
	{
		return EffectManagers.at(ID);
	}
	EffectElementData* getEffectLayer(int ID = 0)
	{
		return EffectData[ID];
	}

	ObjDBManager<InterfaceElement>* getInterfaceManager(int ID = 0)
	{
		return InterfaceManagers.at(ID);
	}
	InterfaceElementData* getInterfaceLayer(int ID = 0)
	{
		return InterfaceData[ID];
	}

	//TODO : Finish this part too.
};


