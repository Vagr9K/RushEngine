#include <iostream>
#include <vector>
using namespace std;
#include "Box2D.h"


class MainObj 
{
public:
	

};



class MinObj 
{
public:




};

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

