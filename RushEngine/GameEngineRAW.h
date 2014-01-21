#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Objects/Objects.h"
#include "Audio/Audio.h"

#include "AdvFeatures/Tests.h"

class GameEngine
{
private:
	string Title;
	int h, w, LayerNumber;
	ObjectsEngine* Objects;
	string Errors;
	
	void InitOldCpp()
	{
		Physics = NULL;
		Objects = NULL;
		Graphics = NULL;
	}

	
public:
	PhysicsEngine* Physics;
	GraphicsEngine* Graphics;
	EventingEngine* Eventing;
	AudioEngine* Audio;
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
		Eventing = new EventingEngine();
		Audio = new AudioEngine(Eventing);
	}
	void InitGraphics(int Width, int Height, string Title)
	{
		this->h = Height;
		this->w = Width;
		this->Title = Title;
		Graphics = new GraphicsEngine;
		if (Objects == NULL)
		{
			Eventing->SystemEvents->GraphicsError("Objects engine is not initialized.");
		}
		
		Graphics->Init(Width, Height, LayerNumber, Title, Eventing, Objects);
		

	}

	bool DeleteGraphics()
	{
		bool Status = Graphics->Stop();

		return Status;
	}

	EventingEngine* getEventingEngine()
	{
		return Eventing;
	}
	ObjectsEngine* getObjects()
	{
		return Objects;
	}

};

