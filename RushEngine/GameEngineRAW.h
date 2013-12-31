#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Objects/ObjectsEngine.h"



class GameEngine
{
private:
	string Title;
	int h, w, LayerNumber;
	
	string Errors;
	EventingEngine EventEngine;

public:
	PhysicsEngine* Physics;
	ObjectsEngine* Objects;
	GraphicsEngine* Graphics;

	void InitPhysics()
	{
		Physics = new PhysicsEngine;
	}
	void DeletePhysics()
	{

	}
	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount);
	}
	
	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount, int OptimalObjectsCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount, OptimalObjectsCount);
	}
	void DeletObjects()
	{

	}
	GameEngine()
	{ 
		
	}
	void InitGraphics(int Width, int Height, int LayerNumber, string Title)
	{
		this->h = Height;
		this->w = Width;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		Graphics = new GraphicsEngine;
		Graphics->Init(Width, Height, LayerNumber, Title, &EventEngine);
		

	}

	bool DeleteGraphics()
	{
		bool Status = Graphics->Stop();

		return Status;
	}

	EventingEngine* getEventingEngine()
	{
		return &EventEngine;
	}

};

class OPSTester
{
	time_t startFPS, endFPS;
	bool FPSStarted;
	double FPSTestTime;
	int Frames;
	EventingEngine event;
private:
	void InitOldCpp()
	{
		FPSStarted = false;
		Frames = 0;
	}
public:
	void TestOPS(double TestTime)
	{
		InitOldCpp();
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
				event.SystemEvents.OPSLog(ToString.str());
				FPSStarted = false;
			}
			else
			{
				Frames++;
			}
		}
	}
};
