#pragma once

#include <vector>
#include "Object.h"
#include "Effects.h"
#include "Interface.h"
#include "Background.h"


typedef vector <ObjDBManager<ObjectElement>*> ObjectElementManagers;
typedef vector <ObjectElement*> ObjectElementData;

typedef vector <ObjDBManager<EffectElement>*> EffectElementManagers;
typedef vector <EffectElement*> EffectElementData;

typedef vector <ObjDBManager<InterfaceElement>*> InterfaceElementManagers;
typedef vector <InterfaceElement*> InterfaceElementData;

typedef vector <ObjDBManager<BackgroundElement>*> BackgroundElementManagers;
typedef vector <BackgroundElement*> BackgroundElementData;

typedef ObjDBManager<AudioElement> AudioElementManager;
typedef vector<AudioElement*> AudioElementData;

class ObjectsEngine
{
  int InterfaceLayerCount;
  int WorldCount;
  int BackgroundLayerCount;
  int EffectLayerCount;
public:
  int OptObjCount;
private:
  ObjectElementManagers ObjectsManagers;
  ObjectElementData * * ObjectsData;

  EffectElementManagers EffectManagers;
  EffectElementData * * EffectData;

  InterfaceElementManagers InterfaceManagers;
  InterfaceElementData * * InterfaceData;

  BackgroundElementManagers BackgroundManagers;
  BackgroundElementData * * BackgroundData;

  AudioElementManager* AudioManager;
  AudioElementData* AudioData;

private:
  void InitOldCpp ();
  void InitObjects (int WorldCount);
  void InitEffect (int WorldCount);
  void InitInterface (int InterfaceCount);
  void InitBackground (int BackgroundCount);
  void InitAudio();
  void DefContructor (int InterfaceLayerCount, int EffectLayerCount, int WorldCount, int BackgroundLayerCount, bool InitAudio = true);
public:
  ObjectsEngine (int InterfaceLayerCount, int EffectsLayerCount, int WorldCount, int BackgroundLayerCount);
  ObjectsEngine (int InterfaceLayerCount, int EffectsLayerCount, int WorldCount, int BackgroundLayerCount, int OptimalObjectsCount);
  int GetCount ();
  int GetEffectLCount ();
  int GetWorldLCount ();
  int GetInterfaceLCount ();
  int GetBackgroundLCount ();
  ObjDBManager <ObjectElement> * getObjectManager (int ID = 0);
  ObjectElementData * getObjectsLayer (int ID = 0);
  ObjDBManager <EffectElement> * getEffectManager (int ID = 0);
  EffectElementData * getEffectLayer (int ID = 0);
  ObjDBManager <InterfaceElement> * getInterfaceManager (int ID = 0);
  InterfaceElementData * getInterfaceLayer (int ID = 0);
  ObjDBManager <BackgroundElement> * getBackgroundManager (int ID = 0);
  BackgroundElementData * getBackgroundLayer (int ID = 0);
  AudioElementManager* getAudioManager();
  AudioElementData* getAudioData();
};
