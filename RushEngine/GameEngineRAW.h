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

class FPSTest
{
	double FPS;
	double StartTime;
	double Frames;
	double LastDiff;
	double MinDiffTime;
public:

	FPSTest(double MinDiffTime = 1000.0)
	{
		FPS = 0.0;
		Frames = 0.0;
		LastDiff = 0.0;
		this->MinDiffTime = MinDiffTime;
		StartTime = SDL_GetTicks();
		
	}
	void PushFrame()
	{
		Frames++;
	}
	double getFPS()
	{
		double EndTime = SDL_GetTicks();
		double DiffTime = EndTime - StartTime;
		if (DiffTime < MinDiffTime)
		{
			return FPS;
		}
		else
		{

			FPS = Frames / DiffTime * 1000;
			LastDiff = DiffTime;
			Frames = 0;
			StartTime = SDL_GetTicks();
			return FPS;
		}
	}
	double getLastDiff()
	{
		return LastDiff;
	}
};
