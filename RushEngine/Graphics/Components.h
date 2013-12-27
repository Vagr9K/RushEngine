#include <string>
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
