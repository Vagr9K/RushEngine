
#include "Background.h"

void BackgroundBASE::CleanBackground (void * Obj)
        {
		delete Obj;
		Obj = NULL;
	}
void BackgroundBASE::NULLifyAll ()
        {

		DatabaseManager = NULL;
		ObjElement = NULL;

	}
void BackgroundBASE::InitOldCpp ()
        {

		DatabaseManager = NULL;
		ObjElementInDB = false;
		ObjElement = NULL;
		InstantPush = false;
	}
void BackgroundBASE::InitObjElement ()
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
BackgroundBASE::BackgroundBASE (ObjDBManager <BackgroundElement> * DatabaseManager, EventingEngine * EventsEngine, bool AutoAdd)
        {
		InitOldCpp();
		this->DatabaseManager = DatabaseManager;
		EventingEnginePtr = EventsEngine;
		if (AutoAdd)
		{
			AddToDatabase();
		}
	}
BackgroundBASE::~ BackgroundBASE ()
        {
		DeleteObjElement();
		if (InstantPush == true)
		{
			DatabaseManager->PushChanges();
		}


	}
ObjDBManager <BackgroundElement> * BackgroundBASE::GetDBManager ()
        {
		return DatabaseManager;
	}
void BackgroundBASE::SetImageSource (string Source)
        {
		ObjElement->Image->Source = Source;
	}
string BackgroundBASE::GetImageSource ()
        {
		return ObjElement->Image->Source;
	}
void BackgroundBASE::AddToDatabase ()
        {
		if (ObjElement == NULL)
		{
			InitObjElement();
		}
		DatabaseManager->AddToCreate(ObjElement);
		ObjElementInDB = true;
	}
void BackgroundBASE::DeleteFromDatabase ()
        {
		if (ObjElement == NULL)
		{
			throw "ObjElement is not initialized.";
		}
		DatabaseManager->AddToDelete(ObjElement);
		ObjElementInDB = false;
	}
void BackgroundBASE::PushManagerChanges ()
        {
		DatabaseManager->PushChanges();
	}
void BackgroundBASE::DeleteObjElement ()
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
void BackgroundBASE::AddImage (IMG * Image)
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
void BackgroundBASE::AddText (TXT * Text)
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
void BackgroundBASE::DeleteImage ()
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
void BackgroundBASE::DeleteText ()
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
void BackgroundBASE::SetTextFont (TextFont * Font)
        {
		ObjElement->Text->Font = Font;
		ObjElement->TextExists = true;
	}
void BackgroundBASE::SetTextColorFG (SDL_Color * Foreground)
        {
		ObjElement->Text->Foreground = Foreground;
	}
void BackgroundBASE::SetTextColorBG (SDL_Color * Background)
        {
		ObjElement->Text->Background = Background;
	}
void BackgroundBASE::SetTextContent (string Content)
        {
		ObjElement->Text->Content = Content;
	}
void BackgroundBASE::SetTextDrawMode (Mode DrawMode)
        {
		ObjElement->Text->DrawMode = DrawMode;
	}
