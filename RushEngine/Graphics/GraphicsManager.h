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
  vector <SDL_Surface*> * PreLoadedSurfCPU;
  vector <SDL_Texture*> * PreLoadedTextGPU;
  vector <string> * PreLoadedPathsCPU;
  vector <string> * PreLoadedPathsGPU;
  EventingEngine * EventEngine;
  SDL_Renderer * Renderer;
  int OptimalObjectCount;
  vector <TTF_Font*> LoadedFonts;
  vector <string> LoadedFontsPaths;
  vector <SDL_Surface*> LoadedTextsCPU;
  vector <string> LoadedTextArgsCPU;
  vector <string> LoadedTextArgsGPU;
  vector <string> LoadedTextArgsGL;
  vector <SDL_Texture*> LoadedTextsGPU;
  vector <GLuint> LoadedTextsGL;
  vector <int> TimeFromLastUseCPU;
  vector <int> TimeFromLastUseGPU;
  vector <int> TimeFromLastUseGL;
  int MaximumTimeFromLastUseOfText;
  vector <string> * PreLoadedPathsGL;
  vector <GLuint> * PreLoadedTextGL;
private:
  void InitOldCpp ();
public:
  GraphicsManager (EventingEngine * EventEngine, SDL_Renderer * Renderer, vector <SDL_Surface*> * PreLoadedSurfCPU, vector <SDL_Texture*> * PreLoadedTextGPU, vector <GLuint> * PreLoadedTextGL, vector <string> * PreLoadedPathsCPU, vector <string> * PreLoadedPathsGPU, vector <string> * PreLoadedPathsGL);
  GraphicsManager (EventingEngine * EventEngine, SDL_Renderer * Renderer);
  GraphicsManager (EventingEngine * EventEngine, SDL_Renderer * Renderer, int OptimalObjectCount);
  void SetOptimalObjectCount (int OptimalObjectCount);
  int GetOptimalObjectCount ();
  void SetMaximumTimeOfText (int Time);
  int GetMaximumTimeOfText ();
  void InitPreloaders ();
  void CleanTextSurfaceCPU (int IndexOfItem);
  void CleanTextTextureGPU (int IndexOfItem);
  void CleanTextTextureGL (int IndexOfItem);
  TTF_Font * LoadFont (string FontPath, int PointSize, int Index = 0);
  TTF_Font * GetFont (string FontPath, int PointSize, int FontOutline, Style FontStyle, int Index = 0, bool FontKerning = false);
  SDL_Surface * GetTextImageCPU (TextFont * Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background);
  SDL_Texture * GetTextImageGPU (TextFont * Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background);
  GLuint GetTextImageGL (TextFont * Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background);
  SDL_Surface * GetSurfaceSolid (TTF_Font * Font, string Text, SDL_Color Foreground);
  SDL_Texture * GetTextureSolid (TTF_Font * Font, string Text, SDL_Color Foreground);
  SDL_Surface * GetSurfaceShaded (TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Texture * GetTextureShaded (TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Surface * GetSurfaceBlended (TTF_Font * Font, string Text, SDL_Color Foreground);
  GLuint GetTextureBlendedGL (TTF_Font * Font, string Text, SDL_Color Foreground);
  SDL_Texture * GetTextureBlended (TTF_Font * Font, string Text, SDL_Color Foreground);
  GLuint GetTextureSolidGL (TTF_Font * Font, string Text, SDL_Color Foreground);
  GLuint GetTextureShadedGL (TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background);
  SDL_Surface * LoaderCPU (string Path);
  bool PreLoadCPU (string Path, bool CheckExistance = true);
  void CleanPreLoadCPU (int IndexOfItem);
  void ClearPreLoadCPU (double PartToClear);
  SDL_Surface * IMGLoad (string Path);
  SDL_Texture * LoaderGPU (string Path);
  void PreLoadGPU (string Path, bool CheckExistance = true);
  void CleanPreLoadGPU (int IndexOfItem);
  void ClearPreLoadGPU (double PartToClear);
  GLuint GenerateTexture (SDL_Surface * Surface);
  GLuint GenerateTexture (string Path);
  GLuint LoaderGL (string Path);
  void CleanPreLoadGL (int IndexOfItem);
  void ClearPreLoadGL (double PartToClear);
};

#endif