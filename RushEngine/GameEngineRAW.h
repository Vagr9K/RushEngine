#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Objects/Objects.h"



class GameEngine
{
private:
	string Title;
	int h, w, LayerNumber;
	ObjectsEngine* Objects;
	string Errors;
	EventingEngine EventEngine;
	void InitOldCpp()
	{
		Physics = NULL;
		Objects = NULL;
		Graphics = NULL;
	}

	
public:
	PhysicsEngine* Physics;
	GraphicsEngine* Graphics;

	void InitPhysics()
	{
		Physics = new PhysicsEngine;
	}

	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount);
	}
	
	
	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount, int OptimalObjectsCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount, OptimalObjectsCount);
	}

	GameEngine()
	{ 
		
	}
	void InitGraphics(int Width, int Height, string Title)
	{
		this->h = Height;
		this->w = Width;
		this->Title = Title;
		Graphics = new GraphicsEngine;
		if (Objects == NULL)
		{
			EventEngine.SystemEvents.GraphicsError("Objects engine is not initialized.");
		}
		
		Graphics->Init(Width, Height, LayerNumber, Title, &EventEngine, Objects);
		

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
	ObjectsEngine* getObjects()
	{
		return Objects;
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
