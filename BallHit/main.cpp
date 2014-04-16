#include "GameEngine.h"

#include "Physics.h"
#include "Controls.h"
//Declarations
#define WWIDTH 1000
#define WHEIGHT 900
#define KFactor 100

GameEngine* mainEngine;
b2World* mainWorld;

BallManager* BallMan;
ControlManager* ControlMan;

//Main Init
void Init()
{
	mainWorld = new b2World(b2Vec2(0.f, -9.8f));
	BallMan = new BallManager();

	mainEngine = new GameEngine(false);
	mainEngine->InitPhysics();
	mainEngine->InitObjects(0, 0, 1, 1);
	mainEngine->InitGraphics(WWIDTH, WHEIGHT, "BallHit");
	mainEngine->Graphics->Start();
	mainEngine->Graphics->DrawerGL->setSyncFactor(KFactor);
	mainEngine->Graphics->DrawerGL->setFrameRate(1000);
	mainEngine->Physics->AddWorld(mainWorld);

	ControlMan = new ControlManager(BallMan);
}
//Controls
void RenderControls()
{
	ControlMan->CheckInput();
}


//Physics
Uint32 PhysSincTime = 0;
Uint32 CurrTime = 0;
unsigned int PhysFreq = 1000 / 60;
float WorldStep = 1.f / 60.f;
void RenderPhysics()
{
	//CurrTime = SDL_GetTicks();
	//if ((CurrTime-PhysSincTime) > PhysFreq)
	//{
		mainWorld->Step(WorldStep, 8, 3);
	//	PhysSincTime = SDL_GetTicks();
	//}

}

//Graphics
void RenderGraphics()
{
	mainEngine->Graphics->DrawerGL->StartBuffer();
	mainEngine->Graphics->DrawerGL->SyncObjects(false, IMAGE);
	mainEngine->Graphics->DrawerGL->PushBuffer();
}

//DeInit
void DeInit()
{
	mainEngine->~GameEngine();
}



//Main Loop
int main(int argc, char** argv)
{
	Init();
	bool Close = false;
	while (Close == false)
	{
		mainEngine->Eventing->StartLoop();
		if (mainEngine->Eventing->GlobalEvent.type == SDL_QUIT)
		{
			Close = true;
		}
		RenderControls();
		RenderPhysics();
		RenderGraphics();
		mainEngine->Eventing->EndLoop();

	}


	return 0;
}