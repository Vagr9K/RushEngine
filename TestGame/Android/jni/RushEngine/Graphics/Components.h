#pragma once

#include <string>
#include <ctime>
#ifdef _WIN32
#include <SDL_opengl.h>
#elif defined __ANDROID__
#include <SDL_opengles.h>
#else
#error "Unknown platform."
#endif



using namespace std;

enum Mode
{
  SOLID,
 // SHADED,  //No support because of OpenGL problems.
  BLENDED
};
enum Style
{
  NORMAL,
  BOLD,
  ITALIC,
  STRIKETHROUGH,
  UNDERLINE
};
class GameEngine;
struct TextFont
{
  string FontPath;
  int PointSize;
  int FontOutline;
  Style FontStyle;
  int Index;
  bool FontKerning;
private:
  void InitOldCpp ();
public:
  TextFont (string FontPath);
};
struct WindowInfo
{
	int Height;
	int Width;
	float AspectX;
	float AspectY;
	int ZeroHeight;
	int ZeroWidth;
	WindowInfo();
};


struct TextureRenderFactor
{
	GLfloat KX;
	GLfloat KY;
	TextureRenderFactor();
	
};

struct TextureInfo
{
	GLuint TextureID;
	TextureRenderFactor KxKy;
};

struct RGBColor
{
	float Fade, R, G, B;
	bool operator==(RGBColor SecondObject);
	
};

enum MSGBOXMODE
{
	ERRORMessage,
	WARNINGMessage,
	INFORMATIONMessage
};