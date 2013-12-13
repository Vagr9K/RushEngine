#include "GameEngine.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#define WHEIGHT 900
#define WWIDTH 1000


#define  BallCount  40
#define  WallCount  4

#define  K 100

const float FPS = 1.f / 120.f;

GameEngine mainEngine;

vector<Object*> Balls(BallCount);
vector<Object*> Walls(WallCount);
b2Vec2 Gravity(0.0f, -10.0f);
b2World World(Gravity);
b2CircleShape* STDShape; 
b2PolygonShape* W1;
b2PolygonShape* W2;

int CamX = 0;
int CamY = 0;

SDL_Event* Ev;

int StartTime = GetTickCount();
int Now = GetTickCount();
int Delta = 0;

bool FPSCheck(float Step)
{
	bool Ret = false;
	Now = GetTickCount();
	Delta = Now - StartTime;

	if (Delta>=Step*1000)
	{
		Ret = true;
	}
	return Ret;
}


int RndGen(int Max)
{
	int Ret = rand() % Max;
	return Ret;
}


void Init()
{
	
	mainEngine.InitPhysics();
	mainEngine.InitGraphics(WWIDTH, WHEIGHT, 1, "Test #002.");
	mainEngine.Graphics->Start();
	mainEngine.Graphics->InitGL();
	mainEngine.InitObjects(0,0,1,0);
	mainEngine.Physics->AddWorld(&World);
	STDShape = new b2CircleShape;
	STDShape->m_p.Set(0.0f, 0.0f);
	STDShape->m_radius = 0.1f;
	W1 = new b2PolygonShape;
	W1->SetAsBox(10.f, 5.f);
	W2 = new b2PolygonShape;
	W2->SetAsBox(5.f, 10.f);
	float Rnd1 = 0;
	float Rnd2 = 0;
	for (int i = 0; i < BallCount; i++)
	{
		Rnd1 = RndGen(10);
		Rnd2 = RndGen(10);
		Balls.at(i) = new Object(&mainEngine, 0, 0);
		Balls.at(i)->BodyDefinition = new b2BodyDef;
		Balls.at(i)->BodyDefinition->type = b2_dynamicBody;
		Balls.at(i)->BodyDefinition->position.Set(Rnd1, Rnd2);
		Balls.at(i)->CreateBody();
		Balls.at(i)->FixtureDefinition = new b2FixtureDef;
		Balls.at(i)->FixtureDefinition->restitution = 1.1f;
		Balls.at(i)->FixtureDefinition->shape = STDShape;
		Balls.at(i)->CreateFixture();


	}

	for (int j = 0; j < WallCount;j++)
	{
		Walls.at(j) = new Object(&mainEngine, 0, 0);
		Walls.at(j)->BodyDefinition = new b2BodyDef;
		Walls.at(j)->BodyDefinition->type = b2_kinematicBody;


		Walls.at(j)->FixtureDefinition = new b2FixtureDef;
		Walls.at(j)->FixtureDefinition->restitution = 1.0f;

	}

	Walls.at(0)->BodyDefinition->position.Set(5.f, -2.5f);
	Walls.at(0)->CreateBody();
	Walls.at(0)->FixtureDefinition->shape = W1;
	Walls.at(0)->CreateFixture();
	Walls.at(1)->BodyDefinition->position.Set(-2.5f, 5.f);
	Walls.at(1)->CreateBody();
	Walls.at(1)->FixtureDefinition->shape = W2;
	Walls.at(1)->CreateFixture();
	Walls.at(2)->BodyDefinition->position.Set(5.f, 12.5f);
	Walls.at(2)->CreateBody();
	Walls.at(2)->FixtureDefinition->shape = W1;
	Walls.at(2)->CreateFixture();
	Walls.at(3)->BodyDefinition->position.Set(12.5f, 5.f);
	Walls.at(3)->CreateBody();
	Walls.at(3)->FixtureDefinition->shape = W2;
	Walls.at(3)->CreateFixture();

	Ev = new SDL_Event;

}


void RenderPhysics()
{
	float Step = 1.f / 70.f;
	World.Step(Step, 10, 3);


}

void RenderGraphics()
{
	float Angle = 0;
	b2Vec2 Pos;
	mainEngine.Graphics->DrawerGL->StartBuffer();
	for (int i = 0; i < BallCount;i++)
	{
		Pos = Balls.at(i)->Body->GetPosition();
		Angle = Balls.at(i)->Body->GetAngle();
		mainEngine.Graphics->DrawerGL->AddToBuffer(Pos.x*K, WHEIGHT - Pos.y*K, 0.2*K, 0.2*K, "Ball.png", Angle);
	}
	
		Pos = Walls.at(0)->Body->GetPosition();
		mainEngine.Graphics->DrawerGL->AddToBuffer(Pos.x * K, WHEIGHT - Pos.y * K, 10 * K, 5 * K, "Wall.png");
		Pos = Walls.at(1)->Body->GetPosition();
		mainEngine.Graphics->DrawerGL->AddToBuffer(Pos.x * K, WHEIGHT - Pos.y * K, 5 * K, 10 * K, "Wall.png");
		Pos = Walls.at(2)->Body->GetPosition();
		mainEngine.Graphics->DrawerGL->AddToBuffer(Pos.x * K, WHEIGHT - Pos.y * K, 10 * K, 5 * K, "Wall.png");
		Pos = Walls.at(3)->Body->GetPosition();
		mainEngine.Graphics->DrawerGL->AddToBuffer(Pos.x * K, WHEIGHT - Pos.y * K, 5 * K, 10 * K, "Wall.png");
	
		mainEngine.Graphics->DrawerGL->PushBuffer();
		
}

void RenderCamera()
{
	const Uint8* A = SDL_GetKeyboardState(NULL);
	if (A[SDL_SCANCODE_RIGHT])
	{
		CamX += 40;
	}
	else if (A[SDL_SCANCODE_LEFT])
	{
		CamX -= 40;
	}
	else if (A[SDL_SCANCODE_UP])
	{
		CamY += 40;
	}
	else if (A[SDL_SCANCODE_DOWN])
	{
		CamY = CamY - 40;
	}
	mainEngine.Graphics->DrawerGL->SetViewPort(CamX, CamY, WHEIGHT, WWIDTH);

}

int main(int argc, char** argv)
{
	Init();
	bool Close=false;
	while (Close==false)
	{
		SDL_PollEvent(Ev);
		if (Ev->type == SDL_QUIT)
		{
			Close = true;
		}
		RenderPhysics();
		
		RenderGraphics();
		
		
		RenderCamera();
	}

	
	return 0;
}
