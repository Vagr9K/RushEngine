#include "GameEngine.h"

using namespace std;

#define WHEIGHT 320
#define WWIDTH 240


#define  BallCount  10
#define  WallCount  4

#define  K 30


Uint32 LastPhysTime = SDL_GetTicks();

GameEngine* mainEngine;


vector<Object*> Balls(BallCount);
vector<Object*> Walls(WallCount);
b2Vec2 Gravity(0.0f, -10.0f);
b2World World(Gravity);
b2CircleShape* STDShape;
b2PolygonShape* W1;
b2PolygonShape* W2;

SDL_Event* Ev;

int StartTime = SDL_GetTicks();
int Now = SDL_GetTicks();
int Delta = 0;

int RndGen(int Max)
{
	
	int Ret = rand() % Max;
	return Ret;
}

void Init()
{
	
	mainEngine = new GameEngine(false);
	mainEngine->InitPhysics();

	mainEngine->InitObjects(0, 0, 1, 0);
	mainEngine->InitGraphics(WWIDTH, WHEIGHT, "Test #004.");
	mainEngine->Graphics->Start();
	mainEngine->Graphics->DrawerGL->CacheImage("Resources/Ball.png");
	mainEngine->Graphics->DrawerGL->CacheImage("Resources/Wall.png");
	mainEngine->Graphics->DrawerGL->setFrameRate(120);

	mainEngine->Physics->AddWorld(&World);

	STDShape = new b2CircleShape;
	STDShape->m_p.Set(0.0f, 0.0f);
	STDShape->m_radius = 0.4f;
	W1 = new b2PolygonShape;
	W1->SetAsBox(10.f, 5.f);
	W2 = new b2PolygonShape;
	W2->SetAsBox(5.f, 10.f);
	b2BodyDef* BodyDefinitionBall = new b2BodyDef;
	BodyDefinitionBall->type = b2_dynamicBody;
	b2FixtureDef* FixtureDefBall = new b2FixtureDef;
	FixtureDefBall->restitution = 1.1f;
	FixtureDefBall->friction = 0.15f;
	FixtureDefBall->shape = STDShape;
	float Rnd1 = (float)RndGen(9)+1.f;
	float Rnd2 = (float)RndGen(9) + 1.f;
	for (int i = 0; i < BallCount; i++)
	{
		BodyDefinitionBall->position.Set(Rnd1, Rnd2);
		Rnd1 = (float)RndGen(9) + 1.f;
		Rnd2 = (float)RndGen(9) + 1.f;
		Balls.at(i) = new Object(0, true, true);
		Balls.at(i)->CreateBody(BodyDefinitionBall);
		Balls.at(i)->CreateFixture(FixtureDefBall);
		Balls.at(i)->SetImageSource("Resources/Ball.png");
		Balls.at(i)->ForceLocalFactor = true;
		Balls.at(i)->SyncFactor = K;

	}
	b2BodyDef* BodyDefinitionWall = new b2BodyDef;
	BodyDefinitionWall->type = b2_kinematicBody;
	b2FixtureDef* FixtureDefWall = new b2FixtureDef;
	FixtureDefWall->restitution = 1.f;
	for (int j = 0; j < WallCount; j++)
	{
		Walls.at(j) = new Object(&World, mainEngine->getObjects()->getObjectManager(0), mainEngine->Eventing, true, true);
		Walls.at(j)->SetImageSource("Resources/Wall.png");
		Walls.at(j)->SyncFactor = K;
		Walls.at(j)->ForceLocalFactor = true;
	}

	BodyDefinitionWall->position.Set(5.f, -2.5f);
	Walls.at(0)->CreateBody(BodyDefinitionWall);
	FixtureDefWall->shape = W1;
	Walls.at(0)->CreateFixture(FixtureDefWall);
	BodyDefinitionWall->position.Set(-2.5f, 5.f);
	Walls.at(1)->CreateBody(BodyDefinitionWall);
	FixtureDefWall->shape = W2;
	Walls.at(1)->CreateFixture(FixtureDefWall);
	BodyDefinitionWall->position.Set(5.f, 12.5f);
	Walls.at(2)->CreateBody(BodyDefinitionWall);
	FixtureDefWall->shape = W1;
	Walls.at(2)->CreateFixture(FixtureDefWall);
	BodyDefinitionWall->position.Set(12.5f, 5.f);
	Walls.at(3)->CreateBody(BodyDefinitionWall);
	FixtureDefWall->shape = W2;
	Walls.at(3)->CreateFixture(FixtureDefWall);

	Ev = new SDL_Event;
	mainEngine->getObjects()->getObjectManager(0)->PushChanges();;
}

void StepWorld()
{
	Uint32 Now = SDL_GetTicks();
	if ((Now - LastPhysTime) > 8)
	{
		float Step = 1.f / 120.f;
		World.Step(Step, 8, 3);

		LastPhysTime = SDL_GetTicks();
	}
	else
	{

	}

}



void RenderPhysics()
{
	StepWorld();
}

void RenderGraphics()
{
	mainEngine->Graphics->DrawerGL->StartBuffer();
	mainEngine->Graphics->DrawerGL->SyncObjects(false, IMAGE);
	mainEngine->Graphics->DrawerGL->PushBuffer();
}



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
		RenderPhysics();

		RenderGraphics();

		mainEngine->Eventing->EndLoop();
		
	}


	return 0;
}