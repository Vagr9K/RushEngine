#include <string>
#include <windows.h>
#include <ctime>
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
	int StartTime;
	int CurrentTime;
	int RepeatsPerSecond;
	double MinDiff;
	OperationController(int RepeatsPerSecond);
	bool GetStatus();

};

