#include <vector>


#include "ObjModel.h"

class ObjDBManager
{
private:
	vector<LayerElement*>* Source;
	vector<LayerElement*>* StoreForDelete;
	vector<LayerElement*>* StoreForAdd;
	int AddCount = 0;
	int DeleteCount = 0;
	bool Inited = false;

public:

	ObjDBManager(vector<LayerElement*>* Source)
	{
		this->Source = Source;
	}
	~ObjDBManager()
	{
		delete StoreForDelete;
		delete StoreForAdd;
		delete Source;

	}
	void SetSource(vector<LayerElement*>* Source)
	{
		CleanStore();
		Init();
		this->Source = Source;
	}
	void Init()
	{
		StoreForAdd = new vector<LayerElement*>;
		StoreForDelete = new vector<LayerElement*>;

	}
	void AddToDelete(LayerElement* DeleteElement)
	{
		if (Inited == false)
		{
			Init();
		}
		StoreForDelete->push_back(DeleteElement);
		DeleteCount++;

	}

	void AddToCreate(LayerElement* NewElement)
	{
		if (Inited == false)
		{
			Init();
		}
		StoreForAdd->push_back(NewElement);
		AddCount++;
	}

	bool PushChanges()
	{
		if (Inited == false)
		{
			return false;
		}
		for (unsigned int i = 0; i < Source->size(); i++)
		{
			for (unsigned int j = 0; j < StoreForDelete->size(); j++)
			{
				if (Source[i] == StoreForDelete[j])
				{
					if (AddCount>0)
					{
						Source[i] = StoreForAdd[AddCount - 1];
						DeleteCount--;
						AddCount--;

					}
					else
					{
						Source->erase(Source->begin() + i);
						DeleteCount--;

					}
					break;
				}
			}
			if (DeleteCount == 0)
			{
				break;
			}
		}
		if (AddCount > 0)
		{
			for (int h = 0; h < AddCount; h++)
			{
				Source->push_back(StoreForAdd->at(h));
			}
		}

		CleanStore();
		return true;
	}
	void CleanStore()
	{
		AddCount = 0;
		DeleteCount = 0;
		bool Inited = false;
		delete StoreForAdd;
		StoreForAdd = NULL;
		delete StoreForDelete;
		StoreForDelete = NULL;
	}

};


class ObjectsEngine
{

	int InterfaceLayerCount;
	int WorldCount;
	int BackgroundLayerCount;
	int SpecialLayerCount;


	
public:
	vector<LayerElement*>* GrLayers;

	vector<ObjDBManager*> *ManagerDB; 
	
	
public:
	ObjectsEngine(int InterfaceLayerCount,int SpecialLayerCount ,int WorldCount, int BackgroundLayerCount)
	{

		this->InterfaceLayerCount = InterfaceLayerCount;
		this->WorldCount = WorldCount;
		this->BackgroundLayerCount = BackgroundLayerCount;
		this->SpecialLayerCount = SpecialLayerCount;
		GrLayers = new vector<LayerElement*>[InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount];
		ObjDBManager* DBPointer;
		for (int i = 0; i <InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount; i++)
		{
			DBPointer = new ObjDBManager(&GrLayers[i]);
			ManagerDB->push_back(DBPointer);
		}

		

	}
	vector<LayerElement*>* GetLayers()
	{
		return GrLayers;
	}

	int GetCount()
	{
		return InterfaceLayerCount + SpecialLayerCount + WorldCount + BackgroundLayerCount;
	}

};


