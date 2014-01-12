#pragma once

#include <vector>
#include "Object.h"

typedef vector<ObjDBManager<ObjectElement>*> LayerElementManagers;
typedef vector<ObjectElement*> LayerElementData;

class ObjectsEngine
{

	int InterfaceLayerCount;
	int WorldCount;
	int BackgroundLayerCount;
	int SpecialLayerCount;



public:
	int OptObjCount;

private:
	LayerElementManagers ObjectsManagers;
	LayerElementData** ObjectsData;

	LayerElementManagers SpecialManagers;
	LayerElementData** SpecialData;


private:
	void InitOldCpp()
	{
		OptObjCount = 0;
	}

	void InitObjects(int WorldCount)
	{
		if (WorldCount != 0)
		{
			ObjectsData = new LayerElementData*[WorldCount];
		}
		else
		{
			ObjectsData = NULL;
		}
		for (int i = 0; i < WorldCount; i++)
		{
			ObjectsData[i] = new LayerElementData;
			ObjectsManagers.push_back(new ObjDBManager<ObjectElement>(ObjectsData[i]));
		}

	}

	void InitSpecial(int WorldCount)
	{
		if (WorldCount != 0)
		{
			SpecialData = new LayerElementData*[WorldCount];
		}
		else
		{
			SpecialData = NULL;
		}
		for (int i = 0; i < WorldCount; i++)
		{
			SpecialData[i] = new LayerElementData;
			SpecialManagers.push_back(new ObjDBManager<ObjectElement>(SpecialData[i]));
		}
	}
	void DefContructor(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackgroundLayerCount)
	{
		InitOldCpp();
		this->InterfaceLayerCount = InterfaceLayerCount;
		this->WorldCount = WorldCount;
		this->BackgroundLayerCount = BackgroundLayerCount;
		this->SpecialLayerCount = SpecialLayerCount;

		/*New API*/
		InitObjects(WorldCount);
		InitSpecial(SpecialLayerCount);



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
		return InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount;
	}

	int GetSpecialLCount()
	{
		return SpecialLayerCount;
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
	LayerElementData* getObjectsLayer(int ID = 0)
	{
		return ObjectsData[ID];
	}
	ObjDBManager<ObjectElement>* getSpecialManager(int ID = 0)
	{
		return SpecialManagers.at(ID);
	}
	LayerElementData* getSpecialLayer(int ID = 0)
	{
		return SpecialData[ID];
	}
	//TODO : Finish this part too.
};


