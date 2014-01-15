#include "ObjectManager.h"
#include <Box2D/Box2D.h>
#include "../Eventing/Eventing.h"



class BackgroundBASE
{
protected:
	ObjDBManager<BackgroundElement> *DatabaseManager;
	int BackgroundsIndex;
	bool ObjElementInDB;
	EventingEngine* EventingEnginePtr;
protected:
	void CleanBackground(void *Obj)
	{
		delete Obj;
		Obj = NULL;
	}

	void NULLifyAll()
	{

		DatabaseManager = NULL;
		ObjElement = NULL;

	}

	void InitOldCpp()
	{

		DatabaseManager = NULL;
		ObjElementInDB = false;
		ObjElement = NULL;
		InstantPush = false;
	}
	void InitObjElement()
	{
		if (ObjElement != NULL)
		{

		}
		else
		{
			ObjElement = new BackgroundElement;
			ObjElement->Image = new IMG();
			ObjElement->ImageExists = true;
			ObjElement->Text = new TXT();
			ObjElement->TextExists = false;
		}
	}
public:
	BackgroundElement *ObjElement;

public:

	bool InstantPush;
public:
	BackgroundBASE(ObjDBManager<BackgroundElement>* DatabaseManager, EventingEngine* EventsEngine, bool AutoAdd = true)
	{
		InitOldCpp();
		this->DatabaseManager = DatabaseManager;
		EventingEnginePtr = EventsEngine;
		if (AutoAdd)
		{
			AddToDatabase();
		}
	}
	~BackgroundBASE()
	{
		DeleteObjElement();
		if (InstantPush == true)
		{
			DatabaseManager->PushChanges();
		}


	}
	ObjDBManager<BackgroundElement> *GetDBManager()
	{
		return DatabaseManager;
	}
	void SetImageSource(string Source)
	{
		ObjElement->Image->Source = Source;
	}
	string GetImageSource()
	{
		return ObjElement->Image->Source;
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
			CleanBackground(ObjElement);

		}
		else
		{
			CleanBackground(ObjElement);

		}
	}

	void AddImage(IMG *Image)
	{
		if (Image == NULL)
			throw "IMG pointer is NULL.";
		if (ObjElement == NULL)
		{

			EventingEnginePtr->SystemEvents->ObjectsError("ObjElement is NULL");
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
			EventingEnginePtr->SystemEvents->ObjectsError("TXT pointer is NULL.");
		}
		if (ObjElement == NULL)
		{
			throw "ObjElement is NULL";
			EventingEnginePtr->SystemEvents->ObjectsError("ObjElement is NULL");
		}
		if (ObjElement->Text != NULL)
		{
			DeleteText();
		}
		ObjElement->Text = Text;
		if (Text->Font != NULL)
		{
			ObjElement->TextExists = true;
		}

	}

	void DeleteImage()
	{
		if (ObjElement->Image == NULL)
		{
			throw "IMG pointer is NULL.";
			EventingEnginePtr->SystemEvents->ObjectsError("IMG pointer is NULL.");
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
			EventingEnginePtr->SystemEvents->ObjectsError("TXT pointer is NULL.");
		}
		delete ObjElement->Text;
		ObjElement->Text = NULL;
		ObjElement->TextExists = false;
	}
	void SetTextFont(TextFont* Font)
	{
		ObjElement->Text->Font = Font;
		ObjElement->TextExists = true;
	}

	void SetTextColorFG(SDL_Color* Foreground)
	{
		ObjElement->Text->Foreground = Foreground;
	}
	void SetTextColorBG(SDL_Color* Background)
	{
		ObjElement->Text->Background = Background;
	}
	void SetTextContent(string Content)
	{
		ObjElement->Text->Content = Content;
	}
	void SetTextDrawMode(Mode DrawMode)
	{
		ObjElement->Text->DrawMode = DrawMode;
	}


};
