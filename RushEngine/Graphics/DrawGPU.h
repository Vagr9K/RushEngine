#include "GraphicsManager.h"
using namespace std;

class DrawGPU
{
  SDL_Rect CopyFrom;
  SDL_Rect CopyTo;
  SDL_Renderer * Render;
  SDL_Window * mainWindow;
  GraphicsManager * ManagerGR;
private:
  void InitOldCpp ();
public:
  DrawGPU (GraphicsManager * ManagerGR, SDL_Renderer * Render, SDL_Window * mainWindow, EventingEngine * Events);
  ~ DrawGPU ();
  void StartBuffer ();
  void AddToBuffer (int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source);
  void AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background);
  void AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground);
  void AddToBuffer (int X, int Y, int W, int H, string Source);
  void PushBuffer ();
  void ClearAll ();
};
