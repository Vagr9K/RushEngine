#pragma once

#include <vector>
#include "Object.h"
class ObjectsEngine
{

	int InterfaceLayerCount;
	int WorldCount;
	int BackgroundLayerCount;
	int SpecialLayerCount;


	
public:
	vector<vector<LayerElement*>*> GrLayers;

	vector<ObjDBManager*> ManagerDB; 
	int OptObjCount;
private:
	void InitOldCpp()
	{
		OptObjCount = 0;
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
			ManagerDB.push_back(new ObjDBManager(GrLayers.at(i)));
		}

		

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
			ManagerDB.push_back(new ObjDBManager(GrLayers.at(i), OptimalObjectsCount));
		}



	}
	vector<vector<LayerElement*>*> GetLayers()
	{
		return GrLayers;
	}

	int GetCount()
	{
		return InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount;
	}

};


