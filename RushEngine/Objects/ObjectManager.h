#pragma once

#include "ObjModel.h"


template <typename ElementType>
class ObjDBManager
{
private:
  vector <ElementType*> * Source;
  vector <ElementType*> * StoreForDelete;
  vector <ElementType*> * StoreForAdd;
  int AddCount;
  int DeleteCount;
  int OptObjCount;
  bool Inited;
private:
  void InitOldCpp ();
public:
  ObjDBManager (vector <ElementType*> * Source);
  ObjDBManager (vector <ElementType*> * Source, int OptimalObjectCount);
  ~ ObjDBManager ();
  void SetOptimalObjectCount (int OptimalObjectCount);
  int GetOptimalObjectCount ();
  void SetSource (vector <ElementType*> * Source);
  void Init ();
  void AddToDelete (ElementType * DeleteElement);
  void AddToCreate (ElementType * NewElement);
  bool PushChanges ();
  void CleanStore ();
};
template <typename ElementType>
void ObjDBManager <ElementType>::InitOldCpp ()
        {
		AddCount = 0;
		DeleteCount = 0;
		OptObjCount = 0;
		Inited = false;
	}
template <typename ElementType>
ObjDBManager <ElementType>::ObjDBManager (vector <ElementType*> * Source)
        {
		InitOldCpp();
		this->Source = Source;
	}
template <typename ElementType>
ObjDBManager <ElementType>::ObjDBManager (vector <ElementType*> * Source, int OptimalObjectCount)
        {
		InitOldCpp();
		this->Source = Source;
		this->OptObjCount = OptimalObjectCount;
	}
template <typename ElementType>
ObjDBManager <ElementType>::~ ObjDBManager ()
        {
		delete StoreForDelete;
		delete StoreForAdd;
		delete Source;

	}
template <typename ElementType>
void ObjDBManager <ElementType>::SetOptimalObjectCount (int OptimalObjectCount)
        {
		this->OptObjCount = OptimalObjectCount;
	}
template <typename ElementType>
int ObjDBManager <ElementType>::GetOptimalObjectCount ()
        {
		return OptObjCount;
	}
template <typename ElementType>
void ObjDBManager <ElementType>::SetSource (vector <ElementType*> * Source)
        {
		CleanStore();
		Init();
		this->Source = Source;
	}
template <typename ElementType>
void ObjDBManager <ElementType>::Init ()
        {
		StoreForAdd = new vector<ElementType*>;
		StoreForAdd->reserve(OptObjCount);
		StoreForDelete = new vector<ElementType*>;
		StoreForDelete->reserve(OptObjCount);

		Inited = true;

	}
template <typename ElementType>
void ObjDBManager <ElementType>::AddToDelete (ElementType * DeleteElement)
        {
		if (Inited == false)
		{
			Init();
		}
		StoreForDelete->push_back(DeleteElement);
		DeleteCount++;

	}
template <typename ElementType>
void ObjDBManager <ElementType>::AddToCreate (ElementType * NewElement)
        {
		if (Inited == false)
		{
			Init();
		}
		StoreForAdd->push_back(NewElement);
		AddCount++;
	}
template <typename ElementType>
bool ObjDBManager <ElementType>::PushChanges ()
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
template <typename ElementType>
void ObjDBManager <ElementType>::CleanStore ()
        {
		AddCount = 0;
		DeleteCount = 0;
		Inited = false;
		delete StoreForAdd;
		StoreForAdd = NULL;
		delete StoreForDelete;
		StoreForDelete = NULL;
	}
