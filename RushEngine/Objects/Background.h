#include "ObjectManager.h"
#include <Box2D/Box2D.h>
#include "../Eventing/Eventing.h"


class BackgroundBASE
{
protected:
  ObjDBManager <BackgroundElement> * DatabaseManager;
  int BackgroundsIndex;
  bool ObjElementInDB;
  EventingEngine * EventingEnginePtr;
protected:
  void CleanBackground (void * Obj);
  void NULLifyAll ();
  void InitOldCpp ();
  void InitObjElement ();
public:
  BackgroundElement * ObjElement;
public:
  bool InstantPush;
public:
  BackgroundBASE (ObjDBManager <BackgroundElement> * DatabaseManager, EventingEngine * EventsEngine, bool AutoAdd = true);
  ~ BackgroundBASE ();
  ObjDBManager <BackgroundElement> * GetDBManager ();
  void SetImageSource (string Source);
  string GetImageSource ();
  void AddToDatabase ();
  void DeleteFromDatabase ();
  void PushManagerChanges ();
  void DeleteObjElement ();
  void AddImage (IMG * Image);
  void AddText (TXT * Text);
  void DeleteImage ();
  void DeleteText ();
  void SetTextFont (TextFont * Font);
  void SetTextColorFG (SDL_Color * Foreground);
  void SetTextColorBG (SDL_Color * Background);
  void SetTextContent (string Content);
  void SetTextDrawMode (Mode DrawMode);
};
