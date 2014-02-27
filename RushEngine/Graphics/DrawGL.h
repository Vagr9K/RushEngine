#include "GraphicsManager.h"


using namespace std;

class DrawGL
{
  SDL_Window * mainWindow;
  GraphicsManager * ManagerGR;
  EventingEngine * EventEngine;
  ObjectsEngine* ObjEngine;
  SDL_GLContext ContextGL;
  int ZeroWidth;
  int ZeroHeight;
  int WinHeight;
  int WinWidth;
  float AspectX;
  float AspectY;
  int DeltaX;
  int DeltaY;
  int BgkC;
  int WorldLC;
  int EffectLC;
  int InterfaceLC;
  bool BufferStarted;
  float GlobalDrawFactor;
  GLuint PrevTextureID;
  RGBColor PrevColor;
  bool BindAllGL;
  Uint32 LastFrameTime;
  int FrameRate;
  bool AllowDraw;
  bool BlendEnabled;
private:
  void InitOldCpp ();
  bool GLErrorTest (string FuntionName);
  bool InitOpenGL ();
  void ManageTexture (GLuint TextureID, GLfloat H, GLfloat W, GLfloat * Trg1Sz, GLfloat * Trg2Sz, GLfloat * Trg1Crd, GLfloat * Trg2Crd);
inline  void AddToBufferFROMTEXTURE(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextureInfo TextureData, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ, bool NoDelta = false, RGBColor* TextureColor = NULL, bool BindAll = false);
  void AddToBufferFROMPATH (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void AddToBufferFROMTEXT (GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont * Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ);
  void DrawFromLayerElement(ObjectElement* Element, float DrawFactor, ObjectSyncMode SyncTo);
  void DrawFromInterfaceElement(InterfaceElement* CurrentElement);
  void DrawFromEffectElement(EffectElement* EffectEl, EffectSyncMode SyncMode, RGBColor* ParticleColor, TextureInfo* TInfo);
  void DrawFromBackgroundElement(BackgroundElement* Element);
  void RefreshData(int NewWidth, int NewHeight);
  void CheckScreenState();
  bool CheckFrames();
  bool CheckDrawAllowance();
inline  bool CheckScreenZone(float x, float y, float h, float w, bool NoDelta = false);
inline void SetEffectMode(bool Status);
public:
  DrawGL (GraphicsManager * ManagerGR, SDL_Window * mainWindow, EventingEngine * Events);
  ~ DrawGL ();
  void SetView(int X, int Y);
  void setSyncFactor(float Factor);
  float getSyncFactor();
  int getFrameRate();
  void setFrameRate(int FrameRate);
  void CacheImage(string Path);
  void CacheText(TextFont* Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background);
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
  void SyncObjects(bool AutoPushBuffer = false, ObjectSyncMode SyncTo = IMAGE);
  void SyncEffects(bool AutoPushBuffer = false, EffectSyncMode SyncMode = ACTIVE);
  void SyncInterface(bool AutoPushBuffer = false);
  void SyncBackground(bool AutoPushBuffer = false);
  void SyncAll(bool AutoPushBuffer = false);
  void PushBuffer ();
  void ClearAll ();
};
