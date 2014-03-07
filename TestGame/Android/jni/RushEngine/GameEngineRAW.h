#pragma once

#include "Graphics/Graphics.h"
#include "Physics/Physics.h"
#include "Objects/Objects.h"
#include "Audio/Audio.h"

#include "AdvFeatures/RuntimeInfo.h"



RuntimeInfo RushEngineInfo;

class GameEngine
{
private:
	string Title;
	int h, w;
	ObjectsEngine* Objects;
	string Errors;
	
	void InitOldCpp()
	{
		Physics = NULL;
		Objects = NULL;
		Graphics = NULL;
	}

	void SyncInfo()
	{
			ObjectsEngine* Obj = this->getObjects();
			if (Obj->GetBackgroundLCount() > 0)
			{
				RushEngineInfo.BackgroundDatabase = Obj->getBackgroundManager(RushEngineInfo.DefaultBackManagerID);
			}
			else
			{
				RushEngineInfo.BackgroundDatabase = NULL;
			}
			if (Obj->GetEffectLCount() > 0)
			{
				RushEngineInfo.EffectDatabase = Obj->getEffectManager(RushEngineInfo.DefaultBackManagerID);
			}
			else
			{
				RushEngineInfo.EffectDatabase = NULL;
			}
			if (Obj->GetInterfaceLCount() > 0)
			{
				RushEngineInfo.InterfaceDatabase = Obj->getInterfaceManager(RushEngineInfo.DefaultBackManagerID);
			}
			else
			{
				RushEngineInfo.InterfaceDatabase = NULL;
			}

			if (Obj->GetWorldLCount() > 0)
			{
				RushEngineInfo.ObjectsDatabase = Obj->getObjectManager(RushEngineInfo.DefaultBackManagerID);
			}
			else
			{
				RushEngineInfo.ObjectsDatabase = NULL;
			}
			RushEngineInfo.Objects = Obj;
	}
public:
	PhysicsEngine* Physics;
	GraphicsEngine* Graphics;
	EventingEngine* Eventing;
	AudioEngine* Audio;
	void InitPhysics()
	{
		Physics = new PhysicsEngine;
		RushEngineInfo.Physics = Physics;
	}

	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount);
		SyncInfo();
	}
	
	
	void InitObjects(int InterfaceLayerCount, int SpecialLayerCount, int WorldCount, int BackGroundLayerCount, int OptimalObjectsCount)
	{
		Objects = new ObjectsEngine(InterfaceLayerCount, SpecialLayerCount, WorldCount, BackGroundLayerCount, OptimalObjectsCount);
		SyncInfo();
	}

	GameEngine()
	{ 
		
		Eventing = new EventingEngine();
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Eventing->SystemEvents->GraphicsError(SDL_GetError());
		}
		Audio = new AudioEngine(Eventing);
		RushEngineInfo.GamePointer = this;
		RushEngineInfo.Eventing = Eventing;

	}
	~GameEngine()
	{
		delete Objects;
		delete Physics;
		delete Graphics;
		delete Eventing;
		delete Audio;
		SDL_Quit();
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
		Graphics->Init(Width, Height, Title, Eventing, Objects);

	}

	bool DeleteGraphics()
	{
		bool Status = Graphics->Stop();

		return Status;
	}

	ObjectsEngine* getObjects()
	{
		return Objects;
	}

};

