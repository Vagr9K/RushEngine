#include "Graphics.h"
#include "Objects.h"
#include "Physics.h"


class GameEngine
{
private:
	string Title;
	int h, w, LayerNumber;
	
	string Errors;
	GEEventing EvSys;

public:
	PhysicsEngine* Physics;
	ObjectsEngine* Objects;
	GraphicsEngine* Graphics;

	void InitPhysics()
	{
		Physics = new PhysicsEngine;
	}

	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount);
	}

	GameEngine()
	{ 
		
	}
	bool StartGraphics(int Width, int Height, int LayerNumber, string Title)
	{
		this->h = Height;
		this->w = Width;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		Graphics = new GraphicsEngine;
		Graphics->Init(Width, Height, LayerNumber, Title, &EvSys);
		return Graphics->Start();

	}



	bool StopGraphics()
	{
		return Graphics->Stop();
	}

	void DelayGraphics(int Milliseconds)
	{
		Graphics->DelayGraphics(Milliseconds);
	}
	void BlackInitGraphics()
	{
		Graphics->BlackInit();
	}
	GEEventing getEventSystem()
	{
		return EvSys;
	}

};

class OPSTester
{
	time_t startFPS, endFPS;
	bool FPSStarted = false;
	double FPSTestTime;
	int Frames = 0;
	GEEventing event;
public:
	void TestOPS(double TestTime)
	{
		if (FPSStarted == false)
		{

			time(&startFPS);
			FPSStarted = true;
			FPSTestTime = TestTime;
			Frames = 1;
		}
		else
		{

			time(&endFPS);
			double DiffTime = difftime(endFPS, startFPS);
			if (DiffTime >= FPSTestTime)
			{
				double FPSActual = Frames/DiffTime;
				std::ostringstream ToString;
				ToString << FPSActual;
				event.OPSLog(ToString.str());
				FPSStarted = false;
			}
			else
			{
				Frames++;
			}
		}
	}
};