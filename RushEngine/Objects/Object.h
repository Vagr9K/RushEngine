#include "ObjectManager.h"
#include <Box2D/Box2D.h>
#include "../Eventing/Eventing.h"



class ObjectBASE
{
protected:
	ObjDBManager *DatabaseManager;
	
	b2World *ObjWorld;
	int PhysicsWorldIndex;
	int ObjectsIndex;
	bool ObjElementInDB;
	EventingEngine* EventingEnginePtr;
public:
	enum SYNCPATH
	{
		IMAGE,
		TEXT,
		ALL,
	};


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
		Body = NULL;
		Fixture = NULL;
		ObjElement = NULL;
		
	}

	void InitOldCpp()
	{
		
		DatabaseManager = NULL;
		ObjWorld = NULL;
		ObjElementInDB = false;
		Body = NULL;
		Fixture = NULL;
		ObjElement = NULL;
		InstantPush = false;
		SyncFactor = 1.0;
		ForceLocalFactor = false;
		SyncGraphics = false;
		AllowDraw = false;
	}
	void InitObjElement()
	{
		if (ObjElement != NULL)
		{

		}
		else
		{
			ObjElement = new LayerElement;
			ObjElement->Image = new IMG();
			ObjElement->ImageExists = true;
			ObjElement->Text = new TXT();
			ObjElement->TextExists = true;
			ObjElement->ObjectPtr = this;
		}
	}

		void SyncObjectSizeData(SYNCPATH SyncTo)
	{
		b2Shape::Type ShapeType = Fixture->GetType();
		b2Shape *CShape = Fixture->GetShape();
		float w, h;
		if (ShapeType == b2Shape::e_circle)
		{
			h = 2 * CShape->m_radius;
			w = 2 * CShape->m_radius;
		}
		else if (ShapeType == b2Shape::e_polygon)
		{
			b2PolygonShape* PolShape = (b2PolygonShape*)CShape;
			float MaxX, MinX, MaxY, MinY;
			b2Vec2 Coords = PolShape->GetVertex(0);
			for (int i = 1; i < PolShape->GetVertexCount();i++)
			{
				Coords = PolShape->GetVertex(i);
				if (Coords.x > MaxX)
				{
					MaxX = Coords.x;
				}
				else if (Coords.x < MinX)
				{
					MinX = Coords.x;
				}
				else if (Coords.y > MaxY)
				{
					MaxY = Coords.y;
				}
				else if (Coords.y < MinY)
				{
					MinY = Coords.y;
				}
			}
			w = MaxX - MinX;
			h = MaxY - MinY;

		}
		switch(SyncTo)
		{
			case IMAGE:
			ObjElement->Image->w = w;
			ObjElement->Image->h = h;
			break;
			case TEXT:
			ObjElement->Text->w = w;
			ObjElement->Text->h = h;
			break;
			case ALL:
			ObjElement->Image->w = w;
			ObjElement->Image->h = h;
			ObjElement->Text->w = w;
			ObjElement->Text->h = h;
			break;
		}
		
	}

		void SyncImage(SYNCPATH SyncTo)
		{
			b2Vec2 Pos = Body->GetPosition();
			if (ForceLocalFactor)
			{
				ObjElement->DrawFactor = SyncFactor;
			}
			else
			{
				ObjElement->DrawFactor =  1.f;
			}
			ObjElement->AllowDraw = AllowDraw;
			switch(SyncTo)
			{
				case IMAGE:
					ObjElement->Image->x = Pos.x;
					ObjElement->Image->y = Pos.y;
					ObjElement->Image->Angle = Body->GetAngle();
				break;
				case TEXT:
					ObjElement->Text->x = Pos.x;
					ObjElement->Text->y = Pos.y;
					ObjElement->Text->Angle = Body->GetAngle();
				break;
				case ALL:
					ObjElement->Image->x = Pos.x;
					ObjElement->Image->y = Pos.y;
					ObjElement->Image->Angle = Body->GetAngle();
					ObjElement->Text->x = Pos.x;
					ObjElement->Text->y = Pos.y;
					ObjElement->Text->Angle = Body->GetAngle();
				break;

		}
		
	}

protected:
	LayerElement *ObjElement;
	
public:
	b2Body* Body;
	b2Fixture* Fixture;
	bool InstantPush;
	bool SyncGraphics;
	float SyncFactor;
	bool ForceLocalFactor;
	bool AllowDraw;

	


public:
	ObjectBASE(b2World* ObjWorld, ObjDBManager* DatabaseManager, EventingEngine* EventsEngine, bool SyncGraphics = true, bool AllowDraw = true)
	{
		InitOldCpp();
		this->SyncGraphics = SyncGraphics;
		this->AllowDraw = AllowDraw;
		this->DatabaseManager = DatabaseManager;
		this->ObjWorld = ObjWorld;
		EventingEnginePtr = EventsEngine;
		if(SyncGraphics)
		{
			AddToDatabase();
		}
	}
	~ObjectBASE()
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
	void SetImageSource(string Source)
	{
		ObjElement->Image->Source = Source;
	}
	string GetImageSource()
	{
		return ObjElement->Image->Source;
	}

	void CreateBody(b2BodyDef* BodyDefinition)
	{
		if (BodyDefinition == NULL)
		{
			
			EventingEnginePtr->SystemEvents.ObjectsError("Body definition not initialized.");
			throw "Body definition not initialized.";
		}
		Body = ObjWorld->CreateBody(BodyDefinition);
	}

	void DestroyBody()
	{
		if (Body == NULL)
		{
			
			EventingEnginePtr->SystemEvents.ObjectsError("Body not initialized.");
			throw "Body not initialized.";
		}
		ObjWorld->DestroyBody(Body);
		Body = NULL;
	}
	void CreateFixture(b2FixtureDef* FixtureDefinition)
	{
		if (Body == NULL)
		{
			
			EventingEnginePtr->SystemEvents.ObjectsError("Body not initialized.");
			throw "Body not initialized.";
		}
		if (FixtureDefinition == NULL)
		{
			
			EventingEnginePtr->SystemEvents.ObjectsError("Fixture definition not initialized.");
			throw "Fixture definition not initialized.";
		}
		Fixture = Body->CreateFixture(FixtureDefinition);

	}

	void DestroyFixture()
	{

		if (Fixture == NULL)
		{
			throw "Fixture not initialized.";
			EventingEnginePtr->SystemEvents.ObjectsError("Fixture not initialized.");
		}
		Body->DestroyFixture(Fixture);
		Fixture = NULL;

	}

	void AddToDatabase()
	{
		if (ObjElement == NULL)
		{
			InitObjElement();
		}
		DatabaseManager->AddToCreate(ObjElement);
		ObjElementInDB = true;
	}

	void DeleteFromDatabase()
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
			DeleteFromDatabase();
			ObjElementInDB = false;
			CleanObject(ObjElement);
			
		}
		else
		{
			CleanObject(ObjElement);
			
		}
	}

	void AddImage(IMG *Image)
	{
		if (Image == NULL)
			throw "IMG pointer is NULL.";
		if (ObjElement == NULL)
		{
			
			EventingEnginePtr->SystemEvents.ObjectsError("ObjElement is NULL");
			throw "ObjElement is NULL";
		}
		if (ObjElement->Image != NULL)
		{
			DeleteImage();
		}
		ObjElement->Image = Image;
		ObjElement->ImageExists = true;
	}

	void AddText(TXT *Text)
	{
		if (Text == NULL)
		{
			throw "TXT pointer is NULL.";
			EventingEnginePtr->SystemEvents.ObjectsError("TXT pointer is NULL.");
		}
		if (ObjElement == NULL)
		{
			throw "ObjElement is NULL";
			EventingEnginePtr->SystemEvents.ObjectsError("ObjElement is NULL");
		}
		if (ObjElement->Text != NULL)
		{
			DeleteText();
		}
		ObjElement->Text = Text;
		ObjElement->TextExists = true;
	}

	void DeleteImage()
	{
		if (ObjElement->Image == NULL)
		{
			throw "IMG pointer is NULL.";
			EventingEnginePtr->SystemEvents.ObjectsError("IMG pointer is NULL.");
		}
		else
		{
			delete ObjElement->Image;
			ObjElement->Image = NULL;
			ObjElement->ImageExists = false;
		}
	}

	void DeleteText()
	{
		if (ObjElement->Text == NULL)
		{
			throw "TXT pointer is NULL.";
			EventingEnginePtr->SystemEvents.ObjectsError("TXT pointer is NULL.");
		}
		delete ObjElement->Text;
		ObjElement->Text = NULL;
		ObjElement->TextExists = false;
	}


	

};
