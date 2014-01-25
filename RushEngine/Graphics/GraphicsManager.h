#pragma once


#include <vector>
#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include "../Objects/Objects.h"
#include "Components.h"
class GraphicsManager
{
  EventingEngine * EventEngine;
  ObjectsEngine* ObjEngine;
  int OptimalObjectCount;
  vector <TTF_Font*> LoadedFonts;
  vector <string> LoadedFontsPaths;
  vector <string> LoadedTextArgsGL;
  vector <TextureInfo> LoadedTextsGL;
  vector <int> TimeFromLastUseGL;
  int MaximumTimeFromLastUseOfText;
  vector <string> * PreLoadedPathsGL;
  vector <TextureInfo> * PreLoadedTextGL;
private:
  void InitOldCpp ();
public:
  GraphicsManager(EventingEngine * EventEngine, ObjectsEngine* ObjEngine,vector <TextureInfo> * PreLoadedTextGL, vector <string> * PreLoadedPathsGL);
  GraphicsManager(EventingEngine * EventEngine, ObjectsEngine* ObjEngine);
  GraphicsManager(EventingEngine * EventEngine, ObjectsEngine* ObjEngine, int OptimalObjectCount);
  ~GraphicsManager();
  void SetOptimalObjectCount (int OptimalObjectCount);
  int GetOptimalObjectCount ();
  void SetMaximumTimeOfText (int Time);
  int GetMaximumTimeOfText ();
  ObjectsEngine* GetObjEngine();
  void InitPreloaders ();
  void CleanTextTextureGL (int IndexOfItem);
  TTF_Font * LoadFont (string FontPath, int PointSize, int Index = 0);
  TTF_Font * GetFont (string FontPath, int PointSize, int FontOutline, Style FontStyle, int Index = 0, bool FontKerning = false);
  TextureInfo GetTextImageGL(TextFont * Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background);
  SDL_Surface * GetSurfaceSolid(TTF_Font * Font, string Text, SDL_Color Foreground);
  SDL_Surface * GetSurfaceShaded(TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Surface * GetSurfaceBlended (TTF_Font * Font, string Text, SDL_Color Foreground);
  TextureInfo GetTextureBlendedGL(TTF_Font * Font, string Text, SDL_Color Foreground);
  TextureInfo GetTextureSolidGL(TTF_Font * Font, string Text, SDL_Color Foreground);
  TextureInfo GetTextureShadedGL(TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Surface * IMGLoad (string Path);
  TextureInfo GenerateTexture(SDL_Surface * Surface);
  TextureInfo GenerateTexture(string Path);
  TextureInfo LoaderGL(string Path);
  void CleanPreLoadGL (int IndexOfItem);
  void ClearPreLoadGL (double PartToClear);
  int GetNearestPowerOfTwo(int OldNumber);
  inline int StringToInt(string Argument);
};

