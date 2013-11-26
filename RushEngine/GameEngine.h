#include "GameEngineRAW.h"






class Object
{
	GameEngine* mainEngine = NULL;
	ObjDBManager *DatabaseManager = NULL;
	PhysicsEngine *ObjPhysics=NULL;
	b2World *ObjWorld=NULL;
	int PhysicsWorldIndex;
	int ObjectsIndex;
	bool ObjElementInDB = false;
	EventingEngine* EventingEngine;

private:
	void CleanObject(void *Obj)
	{
		delete Obj;
		Obj = NULL;
	}

	void NULLifyAll()
	{
		mainEngine = NULL;
		DatabaseManager = NULL;
		ObjPhysics = NULL;
		ObjWorld = NULL;
		BodyDefinition = NULL;
		FixtureDefinition = NULL;
		Body = NULL;
		Fixture = NULL;
		ObjElement = NULL;
		Image = NULL;
		Text = NULL;
	}
public:
	b2BodyDef* BodyDefinition = NULL;
	b2FixtureDef* FixtureDefinition = NULL;
	b2Body* Body=NULL;
	b2Fixture* Fixture = NULL;
	LayerElement *ObjElement=NULL;
	IMG *Image=NULL;
	TXT *Text=NULL;
	bool InstantPush = false;



public:
	Object(GameEngine* Engine, int PhysicsWorldIndex, int ObjectsIndex)
	{
		mainEngine = Engine;
		this->ObjectsIndex = ObjectsIndex;
		this->PhysicsWorldIndex = PhysicsWorldIndex;
		DatabaseManager = mainEngine->Objects->ManagerDB.at(ObjectsIndex);
		ObjPhysics = mainEngine->Physics;
		ObjWorld = ObjPhysics->GetWorlds()->at(PhysicsWorldIndex);
		EventingEngine = Engine->getEventingEngine();
	}
	~Object()
	{
		DeleteObjElement();
		if (InstantPush == true)
		{
			DatabaseManager->PushChanges();
		}
		DestroyFixture();
		DestroyBody();

	}
	ObjDBManager *GetDBManager()
	{
		return DatabaseManager;
	}
	PhysicsEngine *GetPhysics()
	{
		return ObjPhysics;
	}
	b2World *GetObjWorld()
	{
		return ObjWorld;
	}

	void CreateBody()
	{
		if (BodyDefinition==NULL)
		{
			throw "Body definition not initialized.";
			EventingEngine->ObjectsError("Body definition not initialized.");
		}
		Body = ObjPhysics->GetWorlds()->at(PhysicsWorldIndex)->CreateBody(BodyDefinition);
	}

	void DestroyBody()
	{
		if (Body == NULL)
		{
			throw "Body not initialized.";
			EventingEngine->ObjectsError("Body not initialized.");
		}
		ObjPhysics->GetWorlds()->at(PhysicsWorldIndex)->DestroyBody(Body);
		Body = NULL;
	}
	void CreateFixture()
	{
		if (Body==NULL)
		{
			throw "Body not initialized.";
			EventingEngine->ObjectsError("Body not initialized.");
		}
		if (FixtureDefinition == NULL)
		{
			throw "Fixture definition not initialized.";
			EventingEngine->ObjectsError("Fixture definition not initialized.");
		}
		Fixture = Body->CreateFixture(FixtureDefinition);

	}

	void DestroyFixture()
	{
		
		if (Fixture == NULL)
		{
			throw "Fixture not initialized.";
			EventingEngine->ObjectsError("Fixture not initialized.");
		}
		Body->DestroyFixture(Fixture);
		Fixture = NULL;

	}
	void InitObjElement()
	{
		if (ObjElement!=NULL)
		{
			throw "ObjElement already initialized.";
			EventingEngine->ObjectsError("ObjElement already initialized.");
		}
		ObjElement = new LayerElement;
		Image = ObjElement->Image;
		Text = ObjElement->Text;
	}

	void InitFixtureDefinition()
	{
		if (FixtureDefinition==NULL)
		{
			FixtureDefinition = new b2FixtureDef;
		}
	}

	void AddObjElementToManager()
	{
		if (ObjElement==NULL)
		{
			InitObjElement();
		}
		DatabaseManager->AddToCreate(ObjElement);
		ObjElementInDB = true;
	}

	void DeleteObjElementFromManager()
	{
		if (ObjElement == NULL)
		{
			throw "ObjElement is not initialized.";
		}
		DatabaseManager->AddToDelete(ObjElement);
		ObjElementInDB = false;
	}
	void PushManagerChanges()
	{
		DatabaseManager->PushChanges();
	}

	void DeleteObjElement()
	{
		if (ObjElementInDB==true)
		{
			DeleteObjElementFromManager();
			ObjElementInDB = false;
			CleanObject(ObjElement);
			Image = NULL;
			Text = NULL;
		}
		else
		{
			CleanObject(ObjElement);
			Image = NULL;
			Text = NULL;
		}
	}

	void AddImage(IMG *Image)
	{
		if (Image==NULL)
			throw "IMG pointer is NULL.";
		if (ObjElement == NULL)
		{
			throw "ObjElement is NULL";
			EventingEngine->ObjectsError("ObjElement is NULL");
		}
		ObjElement->Image = Image;
	}

	void AddText(TXT *Text)
	{
		if (Text == NULL)
		{
			throw "TXT pointer is NULL.";
			EventingEngine->ObjectsError("TXT pointer is NULL.");
		}
		if (ObjElement == NULL)
		{
			throw "ObjElement is NULL";
			EventingEngine->ObjectsError("ObjElement is NULL");
		}
		ObjElement->Text = Text;
	}

	void DeleteImage()
	{
		if (ObjElement->Image == NULL)
		{
			throw "IMG pointer is NULL."; 
			EventingEngine->ObjectsError("IMG pointer is NULL.");
		}
		delete Image;
		Image = NULL;
	}

	void DeleteText()
	{
		if (ObjElement->Text == NULL)
		{
			throw "TXT pointer is NULL.";
			EventingEngine->ObjectsError("TXT pointer is NULL.");
		}
		delete Text;
		Text = NULL;
	}
	
};

class ObjectContainer
{
	private:
		vector<Object*> Objs;



public:
	ObjectContainer()
	{

	}

	void AddObject(Object* Obj)
	{
		Objs.push_back(Obj);
	}
	vector<Object*>* GetObjs()
	{
		return &Objs;
	}
	void DeleteAll()
	{
		Objs.erase(Objs.begin(), Objs.end());
	}

};