#include <iostream>
#include <vector>
using namespace std;
#include <Box2D/Box2D.h>

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
	TXT()
	{

	}
	TXT(float x, float y, float w, float h, float Angle, string Content)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->Angle = Angle;
		this->Content = Content;
	}
	
};
struct IMGDynamic
{

public:
	float *x, *y, *w, *h;
	float* Angle;
	string Source;
	IMGDynamic(float* pX, float* pY, float* pW, float* pH, float* pAngle, string Source)
	{
		x = pX;
		y = pY;
		w = pW;
		h = pH;
		Angle = Angle;
		this->Source = Source;
	}

};

struct TXTDynamic
{

public:
	float *x, *y, *w, *h;
	float* Angle;
	string Content;
	TXTDynamic(float* pX, float* pY, float* pW, float* pH, float* pAngle, string Content)
	{
		x = pX;
		y = pY;
		w = pW;
		h = pH;
		Angle = Angle;
		this->Content = Content;
	}

};
class ObjectBASE;

struct LayerElement
{
public:
	ObjectBASE* ObjectPtr;
	IMG* Image;
	TXT* Text;
	float DrawFactor;
	bool TextExists;
	bool ImageExists;
	bool AllowDraw;
	LayerElement()
	{
		TextExists = false;
		ImageExists = false;
		DrawFactor = 1.f;
		AllowDraw = true;
	}


};

