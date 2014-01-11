#pragma once

#include <vector>
#include "Object.h"

typedef vector<ObjDBManager<LayerElement>*> LayerElementManagers;
typedef vector<LayerElement*> LayerElementData;

class ObjectsEngine
{

	int InterfaceLayerCount;
	int WorldCount;
	int BackgroundLayerCount;
	int SpecialLayerCount;


	
public:
	
	/*OLD API*/
	vector<vector<LayerElement*>*> GrLayers;

	vector<ObjDBManager<LayerElement>*> ManagerDB; 

	int OptObjCount;
	/*END OF OLD API*/

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
		for (int i = 0; i < WorldCount;i++)
		{
			ObjectsData[i] = new LayerElementData;
			ObjectsManagers.push_back(new ObjDBManager<LayerElement>(ObjectsData[i]));
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
			SpecialManagers.push_back(new ObjDBManager<LayerElement>(SpecialData[i]));
		}
	}
public:
	ObjectsEngine(int InterfaceLayerCount,int SpecialLayerCount ,int WorldCount, int BackgroundLayerCount)
	{
		InitOldCpp();
		this->InterfaceLayerCount = InterfaceLayerCount;
		this->WorldCount = WorldCount;
		this->BackgroundLayerCount = BackgroundLayerCount;
		this->SpecialLayerCount = SpecialLayerCount;
		
		for (int i = 0; i <InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount; i++)
		{
			GrLayers.push_back(new vector<LayerElement*>);
			ManagerDB.push_back(new ObjDBManager<LayerElement>(GrLayers.at(i)));
		}

		// TODO : Finish new API
		/*New API*/
		InitObjects(WorldCount);
		InitSpecial(SpecialLayerCount);

		/*New API END*/

	}
	ObjectsEngine(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackgroundLayerCount, int OptimalObjectsCount)
	{
		InitOldCpp();
		this->InterfaceLayerCount = InterfaceLayerCount;
		this->WorldCount = WorldCount;
		this->BackgroundLayerCount = BackgroundLayerCount;
		this->SpecialLayerCount = SpecialLayerCount;
		this->OptObjCount = OptimalObjectsCount;

		for (int i = 0; i < InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount; i++)
		{
			GrLayers.push_back(new vector<LayerElement*>);
			ManagerDB.push_back(new ObjDBManager<LayerElement>(GrLayers.at(i), OptimalObjectsCount));
		}



	}
	vector<vector<LayerElement*>*>* GetLayers()
	{
		return &GrLayers;
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
	ObjDBManager<LayerElement>* getObjectManager(int ID = 0)
	{
		return ObjectsManagers.at(ID);
	}
	LayerElementData* getObjectsLayer(int ID = 0)
	{
		return ObjectsData[ID];
	}
	ObjDBManager<LayerElement>* getSpecialManager(int ID = 0)
	{
		return SpecialManagers.at(ID);
	}
	LayerElementData* getSpecialLayer(int ID = 0)
	{
		return SpecialData[ID];
	}
	//TODO : Finish this part too.
};


