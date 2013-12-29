#include <iostream>
#include <vector>
using namespace std;
#include <Box2D/Box2D.h>

struct IMG
{

public:
	int x, y, w, h;
	double Angle;
	string Source;
	IMG(int x, int y, int w, int h, double Angle, string Source)
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
	int x, y, w, h;
	double Angle;
	string Content;
	TXT(int x, int y, int w, int h, double Angle, string Content)
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
	int *x, *y, *w, *h;
	double* Angle;
	string Source;
	IMGDynamic(int* pX, int* pY, int* pW, int* pH, double* pAngle, string Source)
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
	int *x, *y, *w, *h;
	double* Angle;
	string Content;
	TXTDynamic(int* pX, int* pY, int* pW, int* pH, double* pAngle, string Content)
	{
		x = pX;
		y = pY;
		w = pW;
		h = pH;
		Angle = Angle;
		this->Content = Content;
	}

};


struct LayerElement
{
public:
	IMG* Image;
	TXT* Text;
	bool TextExists;
	bool ImageExists;
	LayerElement()
	{
		TextExists = false;
		ImageExists = false;
	}

};

