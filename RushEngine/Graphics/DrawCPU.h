#include "GraphicsManager.h"
using namespace std;

class DrawCPU
{
  SDL_Window * Window;
  SDL_Surface * WinSurf;
  SDL_Rect CopyFrom;
  SDL_Rect CopyTo;
  GraphicsManager * ManagerGR;
private:
  void InitOldCpp ();
public:
  DrawCPU (GraphicsManager * ManagerGR, SDL_Window * mainWindow);
  ~ DrawCPU ();
  void StartBuffer ();
  void AddToBuffer (int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source);
  void AddToBuffer (int X, int Y, int W, int H, string Source);
  void AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground);
  void AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background);
  void PushBuffer ();
  void ClearAll ();
};
