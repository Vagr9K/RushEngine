#include "GraphicsManager.h"
using namespace std;

class DrawGL
{
  SDL_Window * mainWindow;
  GraphicsManager * ManagerGR;
  EventingEngine * EventEngine;
  SDL_GLContext ContextGL;
  int WinHeight;
  int WinWidth;
  int DeltaX;
  int DeltaY;
  bool BufferStarted;
private:
  void InitOldCpp ();
  bool GLErrorTest (string FuntionName);
  bool InitOpenGL ();
  void ManageTexture (GLuint TextureID, GLfloat H, GLfloat W, GLfloat * Trg1Sz, GLfloat * Trg2Sz, GLfloat * Trg1Crd, GLfloat * Trg2Crd);
  void AddToBufferFROMTEXTURE(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextureInfo TextureData, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void AddToBufferFROMPATH (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void AddToBufferFROMTEXT (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
public:
  DrawGL (GraphicsManager * ManagerGR, SDL_Window * mainWindow, int Height, int Width, EventingEngine * Events);
  ~ DrawGL ();
  void SetView(int X, int Y);
  void StartBuffer ();
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleZ);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleZ);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Background, GLfloat AngleZ);
  void AddToBuffer (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Background);
  void PushBuffer ();
  void ClearAll ();
};
