


class ObjectRAW
{
	
	ObjDBManager *DatabaseManager;
	
	b2World *ObjWorld;
	int PhysicsWorldIndex;
	int ObjectsIndex;
	bool ObjElementInDB;
	EventingEngine* EventingEngine;


protected:
	void CleanObject(void *Obj)
	{
		delete Obj;
		Obj = NULL;
	}

	void NULLifyAll()
	{
		
		DatabaseManager = NULL;
		
		ObjWorld = NULL;
		BodyDefinition = NULL;
		FixtureDefinition = NULL;
		Body = NULL;
		Fixture = NULL;
		ObjElement = NULL;
		Image = NULL;
		Text = NULL;
	}

	void InitOldCpp()
	{
		
		DatabaseManager = NULL;
		ObjWorld = NULL;
		ObjElementInDB = false;
		BodyDefinition = NULL;
		FixtureDefinition = NULL;
		Body = NULL;
		Fixture = NULL;
		ObjElement = NULL;
		Image = NULL;
		Text = NULL;
		InstantPush = false;

	}
protected:
	LayerElement *ObjElement;
	IMG *Image;
	TXT *Text;
public:
	b2BodyDef* BodyDefinition;
	b2FixtureDef* FixtureDefinition;
	b2Body* Body;
	b2Fixture* Fixture;
	bool InstantPush;



public:
	Object(b2World* ObjWorld, ObjDBManager* DatabaseManager, EventingEngine* Events, bool AddToManager)
	{
		InitOldCpp();
		this->DatabaseManager = DatabaseManager;
		this->ObjWorld = ObjWorld;
		EventingEngine = Events;
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
	b2World *GetObjWorld()
	{
		return ObjWorld;
	}

	void CreateBody()
	{
		if (BodyDefinition == NULL)
		{
			throw "Body definition not initialized.";
			EventingEngine->SystemEvents.ObjectsError("Body definition not initialized.");
		}
		Body = ObjWorld->CreateBody(BodyDefinition);
	}

	void DestroyBody()
	{
		if (Body == NULL)
		{
			throw "Body not initialized.";
			EventingEngine->SystemEvents.ObjectsError("Body not initialized.");
		}
		ObjWorld->DestroyBody(Body);
		Body = NULL;
	}
	void CreateFixture()
	{
		if (Body == NULL)
		{
			throw "Body not initialized.";
			EventingEngine->SystemEvents.ObjectsError("Body not initialized.");
		}
		if (FixtureDefinition == NULL)
		{
			throw "Fixture definition not initialized.";
			EventingEngine->SystemEvents.ObjectsError("Fixture definition not initialized.");
		}
		Fixture = Body->CreateFixture(FixtureDefinition);

	}

	void DestroyFixture()
	{

		if (Fixture == NULL)
		{
			throw "Fixture not initialized.";
			EventingEngine->SystemEvents.ObjectsError("Fixture not initialized.");
		}
		Body->DestroyFixture(Fixture);
		Fixture = NULL;

	}
	void InitObjElement()
	{
		if (ObjElement != NULL)
		{
			throw "ObjElement already initialized.";
			EventingEngine->SystemEvents.ObjectsError("ObjElement already initialized.");
		}
		ObjElement = new LayerElement;
		Image = ObjElement->Image;
		Text = ObjElement->Text;
	}

	void InitFixtureDefinition()
	{
		if (FixtureDefinition == NULL)
		{
			FixtureDefinition = new b2FixtureDef;
		}
	}

	void AddObjElementToManager()
	{
		if (ObjElement == NULL)
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
		if (ObjElementInDB == true)
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
		if (Image == NULL)
			throw "IMG pointer is NULL.";
		if (ObjElement == NULL)
		{
			throw "ObjElement is NULL";
			EventingEngine->SystemEvents.ObjectsError("ObjElement is NULL");
		}
		ObjElement->Image = Image;
		ObjElement->ImageExists = true;
	}

	void AddText(TXT *Text)
	{
		if (Text == NULL)
		{
			throw "TXT pointer is NULL.";
			EventingEngine->SystemEvents.ObjectsError("TXT pointer is NULL.");
		}
		if (ObjElement == NULL)
		{
			throw "ObjElement is NULL";
			EventingEngine->SystemEvents.ObjectsError("ObjElement is NULL");
		}
		ObjElement->Text = Text;
		ObjElement->TextExists = true;
	}

	void DeleteImage()
	{
		if (ObjElement->Image == NULL)
		{
			throw "IMG pointer is NULL.";
			EventingEngine->SystemEvents.ObjectsError("IMG pointer is NULL.");
		}
		delete Image;
		Image = NULL;
		ObjElement->TextExists = false;
	}

	void DeleteText()
	{
		if (ObjElement->Text == NULL)
		{
			throw "TXT pointer is NULL.";
			EventingEngine->SystemEvents.ObjectsError("TXT pointer is NULL.");
		}
		delete Text;
		Text = NULL;
		ObjElement->TextExists = false;
	}

};
