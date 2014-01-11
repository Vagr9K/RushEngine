#include "ObjModel.h"

template <class ElementType>
class ObjDBManager
{
private:
	vector<ElementType*>* Source;
	vector<ElementType*>* StoreForDelete;
	vector<ElementType*>* StoreForAdd;
	int AddCount;
	int DeleteCount;
	int OptObjCount;
	bool Inited;
private:
	void InitOldCpp()
	{
		AddCount = 0;
		DeleteCount = 0;
		OptObjCount = 0;
		Inited = false;
	}

public:

	ObjDBManager(vector<ElementType*>* Source)
	{
		InitOldCpp();
		this->Source = Source;
	}
	ObjDBManager(vector<ElementType*>* Source, int OptimalObjectCount)
	{
		InitOldCpp();
		this->Source = Source;
		this->OptObjCount = OptimalObjectCount;
	}
	~ObjDBManager()
	{
		delete StoreForDelete;
		delete StoreForAdd;
		delete Source;

	}
	void SetOptimalObjectCount(int OptimalObjectCount)
	{
		this->OptObjCount = OptimalObjectCount;
	}
	int GetOptimalObjectCount()
	{
		return OptObjCount;
	}
	void SetSource(vector<ElementType*>* Source)
	{
		CleanStore();
		Init();
		this->Source = Source;
	}
	void Init()
	{
		StoreForAdd = new vector<ElementType*>;
		StoreForAdd->reserve(OptObjCount);
		StoreForDelete = new vector<ElementType*>;
		StoreForDelete->reserve(OptObjCount);

		Inited = true;

	}
	void AddToDelete(ElementType* DeleteElement)
	{
		if (Inited == false)
		{
			Init();
		}
		StoreForDelete->push_back(DeleteElement);
		DeleteCount++;

	}

	void AddToCreate(ElementType* NewElement)
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
		Inited = false;
		delete StoreForAdd;
		StoreForAdd = NULL;
		delete StoreForDelete;
		StoreForDelete = NULL;
	}

};