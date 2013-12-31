#ifndef GraphicsManager_H
#define GraphicsManager_H

#include <vector>
#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_opengl.h>
#include "../Objects/ObjectsEngine.h"
#include "Components.h"
class GraphicsManager
{
  EventingEngine * EventEngine;
  int OptimalObjectCount;
  vector <TTF_Font*> LoadedFonts;
  vector <string> LoadedFontsPaths;
  vector <string> LoadedTextArgsGL;
  vector <SDL_Texture*> LoadedTextsGPU;
  vector <GLuint> LoadedTextsGL;
  vector <int> TimeFromLastUseGL;
  int MaximumTimeFromLastUseOfText;
  vector <string> * PreLoadedPathsGL;
  vector <GLuint> * PreLoadedTextGL;
private:
  void InitOldCpp ();
public:
  GraphicsManager (EventingEngine * EventEngine, vector <GLuint> * PreLoadedTextGL, vector <string> * PreLoadedPathsGL);
  GraphicsManager (EventingEngine * EventEngine);
  GraphicsManager (EventingEngine * EventEngine, int OptimalObjectCount);
  void SetOptimalObjectCount (int OptimalObjectCount);
  int GetOptimalObjectCount ();
  void SetMaximumTimeOfText (int Time);
  int GetMaximumTimeOfText ();
  void InitPreloaders ();
  void CleanTextTextureGL (int IndexOfItem);
  TTF_Font * LoadFont (string FontPath, int PointSize, int Index = 0);
  TTF_Font * GetFont (string FontPath, int PointSize, int FontOutline, Style FontStyle, int Index = 0, bool FontKerning = false);
  GLuint GetTextImageGL (TextFont * Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background);
  SDL_Surface * GetSurfaceSolid(TTF_Font * Font, string Text, SDL_Color Foreground);
  SDL_Surface * GetSurfaceShaded(TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Surface * GetSurfaceBlended (TTF_Font * Font, string Text, SDL_Color Foreground);
  GLuint GetTextureBlendedGL (TTF_Font * Font, string Text, SDL_Color Foreground);
  GLuint GetTextureSolidGL (TTF_Font * Font, string Text, SDL_Color Foreground);
  GLuint GetTextureShadedGL (TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Surface * IMGLoad (string Path);
  GLuint GenerateTexture (SDL_Surface * Surface);
  GLuint GenerateTexture (string Path);
  GLuint LoaderGL (string Path);
  void CleanPreLoadGL (int IndexOfItem);
  void ClearPreLoadGL (double PartToClear);
};

#endif