#include "ObjectManager.h"
#include <Box2D/Box2D.h>
#include "../Eventing/Eventing.h"


class ObjectBASE
{
protected:
  ObjDBManager <ObjectElement> * DatabaseManager;
  b2World * ObjWorld;
  int PhysicsWorldIndex;
  int ObjectsIndex;
  bool ObjElementInDB;
public:
protected:
  void CleanObject (void * Obj);
  void NULLifyAll ();
  void InitOldCpp ();
  void InitObjElement ();
  void SyncObjectSizeData (ObjectSyncMode SyncTo);
  void SyncPhysicsData (ObjectSyncMode SyncTo);
protected:
  ObjectElement * ObjElement;
  EventingEngine * EventingEnginePtr;
  bool SizeDataSyncedImage;
  bool SizeDataSyncedText;
public:
  b2Body * Body;
  b2Fixture * Fixture;
  bool InstantPush;
  bool SyncGraphics;
  float SyncFactor;
  bool ForceLocalFactor;
  bool AllowDraw;
public:
  ObjectBASE (b2World * ObjWorld, ObjDBManager <ObjectElement> * DatabaseManager, EventingEngine * EventsEngine, bool SyncGraphics = true, bool AllowDraw = true);
  ~ ObjectBASE ();
  ObjDBManager <ObjectElement> * GetDBManager ();
  b2World * GetObjWorld ();
  void SetImageSource (string Source);
  string GetImageSource ();
  void CreateBody (b2BodyDef * BodyDefinition);
  void DestroyBody ();
  void CreateFixture (b2FixtureDef * FixtureDefinition);
  void DestroyFixture ();
  void AddToDatabase ();
  void DeleteFromDatabase ();
  void PushManagerChanges ();
  void DeleteObjElement ();
  void AddImage (IMG * Image);
  void AddText (TXT * Text);
  void DeleteImage ();
  void DeleteText ();
  void SetTextFont (TextFont * Font);
  void SyncData (ObjectSyncMode SyncTo);
  void SetTextColorFG (SDL_Color * Foreground);
  void SetTextColorBG (SDL_Color * Background);
  void SetTextContent (string Content);
  void SetTextDrawMode (Mode DrawMode);
};
