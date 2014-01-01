#include <string>

#include <windows.h>


#include <ctime>

#include <SDL_opengl.h>
using namespace std;
enum Mode
{
  SOLID,
  SHADED,
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
};

class OperationController  //Windows only!
{
	ULONGLONG StartTime;
	ULONGLONG CurrentTime;
	int RepeatsPerSecond;
	double MinDiff;
	OperationController(int RepeatsPerSecond);
	bool GetStatus();

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