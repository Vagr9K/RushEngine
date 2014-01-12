#pragma once

#include <vector>
#include "Object.h"
#include "Effects.h"

typedef vector<ObjDBManager<ObjectElement>*> ObjectElementManagers;
typedef vector<ObjectElement*> ObjectElementData;

typedef vector<ObjDBManager<EffectElement>*>  EffectElementManagers;
typedef vector<EffectElement*> EffectElementData;

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


		/*New API END*/
	}
public:
	ObjectsEngine(int InterfaceLayerCount,int SpecialLayerCount ,int WorldCount, int BackgroundLayerCount)
	{
		DefContructor(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackgroundLayerCount);

	}
	ObjectsEngine(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackgroundLayerCount, int OptimalObjectsCount)
	{
		DefContructor(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackgroundLayerCount);
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
	//TODO : Finish this part too.
};


