#include "Graphics.h"




class GameEngine
{
private:
	string GameName, Title;
	int h, w, LayerNumber;
	Graphics* MainUnitG;
	string Errors;
	GEEventing EvSys;

public:
	GameEngine(string GameName)
	{ 
		this->GameName = GameName;
	}
	bool StartGraphics(int Width, int Height, int LayerNumber, string Title)
	{
		this->h = Height;
		this->w = Width;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		MainUnitG = new Graphics;
		MainUnitG->Init(Width, Height, LayerNumber, Title, &EvSys);
		return MainUnitG->Start();

	}



	bool StopGraphics()
	{
		return MainUnitG->Stop();
	}

	void DelayGraphics(int Milliseconds)
	{
		MainUnitG->DelayGraphics(Milliseconds);
	}
	void BlackInitGraphics()
	{
		MainUnitG->BlackInit();
	}
	GEEventing getEventSystem()
	{
		return EvSys;
	}

};