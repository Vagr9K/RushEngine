#include "Objects.h"

void ObjectsEngine::InitOldCpp ()
        {
		OptObjCount = 0;
	}
void ObjectsEngine::InitObjects (int WorldCount)
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
void ObjectsEngine::InitEffect (int WorldCount)
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
void ObjectsEngine::InitInterface (int InterfaceCount)
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
void ObjectsEngine::InitBackground (int BackgroundCount)
        {
		if (BackgroundCount != 0)
		{
			BackgroundData = new BackgroundElementData*[BackgroundCount];
		}
		else
		{
			BackgroundData = NULL;
		}
		for (int i = 0; i < BackgroundCount; i++)
		{
			BackgroundData[i] = new BackgroundElementData;
			BackgroundManagers.push_back(new ObjDBManager<BackgroundElement>(BackgroundData[i]));
		}
	}
void ObjectsEngine::DefContructor (int InterfaceLayerCount, int EffectLayerCount, int WorldCount, int BackgroundLayerCount)
        {
		InitOldCpp();
		this->InterfaceLayerCount = InterfaceLayerCount;
		this->WorldCount = WorldCount;
		this->BackgroundLayerCount = BackgroundLayerCount;
		this->EffectLayerCount = EffectLayerCount;


		InitObjects(WorldCount);
		InitEffect(EffectLayerCount);
		InitInterface(InterfaceLayerCount);
		InitBackground(BackgroundLayerCount);
		

	}
ObjectsEngine::ObjectsEngine (int InterfaceLayerCount, int EffectsLayerCount, int WorldCount, int BackgroundLayerCount)
        {
		DefContructor(InterfaceLayerCount, EffectsLayerCount, WorldCount, BackgroundLayerCount);

	}
ObjectsEngine::ObjectsEngine (int InterfaceLayerCount, int EffectsLayerCount, int WorldCount, int BackgroundLayerCount, int OptimalObjectsCount)
        {
		DefContructor(InterfaceLayerCount, EffectsLayerCount, WorldCount, BackgroundLayerCount);
		this->OptObjCount = OptimalObjectsCount;
	}
int ObjectsEngine::GetCount ()
        {
		return InterfaceLayerCount + EffectLayerCount + WorldCount + BackgroundLayerCount;
	}
int ObjectsEngine::GetEffectLCount ()
        {
		return EffectLayerCount;
	}
int ObjectsEngine::GetWorldLCount ()
        {
		return WorldCount;
	}
int ObjectsEngine::GetInterfaceLCount ()
        {
		return InterfaceLayerCount;
	}
int ObjectsEngine::GetBackgroundLCount ()
        {
		return BackgroundLayerCount;
	}
ObjDBManager <ObjectElement> * ObjectsEngine::getObjectManager (int ID)
        {
		return ObjectsManagers.at(ID);
	}
ObjectElementData * ObjectsEngine::getObjectsLayer (int ID)
        {
		return ObjectsData[ID];
	}
ObjDBManager <EffectElement> * ObjectsEngine::getEffectManager (int ID)
    {
		return EffectManagers.at(ID);
	}
EffectElementData * ObjectsEngine::getEffectLayer (int ID)
    {
		return EffectData[ID];
	}
ObjDBManager <InterfaceElement> * ObjectsEngine::getInterfaceManager (int ID)
    {	
		return InterfaceManagers.at(ID);
	}
InterfaceElementData * ObjectsEngine::getInterfaceLayer (int ID)
    {
		return InterfaceData[ID];
	}
ObjDBManager <BackgroundElement> * ObjectsEngine::getBackgroundManager (int ID)
    {
		return BackgroundManagers.at(ID);
	}
BackgroundElementData * ObjectsEngine::getBackgroundLayer (int ID)
    {
		return BackgroundData[ID];
	}

ObjectsEngine::~ObjectsEngine()
{
	delete[] ObjectsData;
	delete[] InterfaceData;
	delete[] BackgroundData;
	delete[] EffectData;
}


