#include <iostream>
#include <vector>
using namespace std;
#include <Box2D/Box2D.h>

#include "../Graphics/Components.h"

struct IMG
{

public:
	float x, y, w, h;
	float Angle;
	string Source;
	IMG()
	{

	}
	IMG(float x, float y, float w, float h, float Angle, string Source)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->Angle = Angle;
		this->Source = Source;
	}
	
};

struct TXT
{
public:
	float x, y, w, h;
	float Angle;
	string Content;
	TextFont* Font;
	SDL_Color* Foreground;
	SDL_Color* Background;
	Mode DrawMode;
	TXT()
	{
		Font = NULL;
		Content = "No content was added!";
		DrawMode = SOLID;
	}
	TXT(float x, float y, float w, float h, float Angle,TextFont* Font, Mode DrawMode,string Content)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->Angle = Angle;
		this->Font = Font;
		this->Content = Content;
		this->DrawMode = DrawMode;
		Foreground = NULL;
		Background = NULL;
	}
	
};
class ObjectBASE;

struct ObjectElement
{
public:
	ObjectBASE* ObjectPtr;
	IMG* Image;
	TXT* Text;
	float DrawFactor;
	bool TextExists;
	bool ImageExists;
	bool AllowDraw;
	ObjectElement()
	{
		TextExists = false;
		ImageExists = false;
		DrawFactor = 0.f;
		AllowDraw = true;
	}


};

enum ObjectSyncMode
{
	IMAGE,
	TEXT,
	ALL,
};
class EffectBASE;
struct Particle
{
	bool Active;
	float Life;
	float X, Y;
	float H, W;
	float Angle;
	float SpeedX, SpeedY;
	float GravityX, GravityY;
	float R, G, B;
	float Fade;
	Particle()
	{
		Active = false;
	}
};

struct EffectElement
{
	EffectBASE* PtrToEffect;
	Particle* ParticleArray;
	string Path;
	int ParticleCount;
	EffectElement(EffectBASE* PtrToEffect, string Path)
	{
		this->PtrToEffect = PtrToEffect;
		this->Path = Path;
		ParticleCount = 0;
	}
	~EffectElement()
	{
		delete[] ParticleArray;
	}
};
enum EffectSyncMode
{
	ACTIVE,
	INACTIVE,
	ALLEFFECTS
};