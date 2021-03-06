#include <iostream>
#include <vector>
using namespace std;
#include <Box2D/Box2D.h>
#include "SDL.h"
#include "SDL_mixer.h"
#include "../Graphics/Components.h"


struct IMG
{
public:
  float x;
  float y;
  float w;
  float h;
  float Angle;
  string Source;
  IMG ();
  IMG (float x, float y, float w, float h, float Angle, string Source);
};
struct TXT
{
public:
  float x;
  float y;
  float w;
  float h;
  float Angle;
  string Content;
  TextFont * Font;
  SDL_Color * Foreground;
  SDL_Color * Background;
  Mode DrawMode;
  TXT ();
  TXT (float x, float y, float w, float h, float Angle, TextFont * Font, Mode DrawMode, string Content);
};
class ObjectBASE;
struct ObjectElement
{
public:
  ObjectBASE * ObjectPtr;
  IMG * Image;
  TXT * Text;
  float DrawFactor;
  bool TextExists;
  bool ImageExists;
  bool AllowDraw;
  RGBColor* Color;
  ObjectElement ();
  ~ObjectElement();
};
enum ObjectSyncMode
{
  IMAGE,
  TEXT,
  ALL
};
class EffectBASE;
class Particle
{
public:
  bool Active;
  float X;
  float Y;
  float H;
  float W;
  float Angle;
  float R;
  float G;
  float B;
  float Fade;
  Particle ();
};
enum EffectDrawMode
{
	NOBLEND,
	BLEND,
	BLACKBLEND
};
struct EffectElement
{
  EffectBASE * PtrToEffect;
  Particle * ParticleArray;
  EffectDrawMode DrawMode;
  string Path;
  int ParticleCount;
  EffectElement (EffectBASE * PtrToEffect, string Path);
  ~ EffectElement ();
};
enum EffectSyncMode
{
  ACTIVE,
  INACTIVE,
  ALLEFFECTS
};

class InterfaceBASE;
struct InterfaceElement
{
public:
  InterfaceBASE * InterfacePtr;
  IMG * Image;
  TXT * Text;
  bool TextExists;
  bool ImageExists;
  bool Hidden;
  InterfaceElement ();
  ~InterfaceElement();
};
struct BackgroundElement
{
public:
  IMG * Image;
  TXT * Text;
  bool TextExists;
  bool ImageExists;
  bool AllowDraw;
  BackgroundElement ();
  ~BackgroundElement()
  {
	  delete Image;
	  delete Text;
  }
};

