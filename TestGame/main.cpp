#include "GameEngine.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

#define WHEIGHT 900
#define WWIDTH 1000


#define  BallCount  30
#define  WallCount  4

#define  K 100

const float FPS = 1.f / 120.f;

GameEngine mainEngine;

vector<ObjectBASE*> Balls(BallCount);
vector<ObjectBASE*> Walls(WallCount);
b2Vec2 Gravity(0.0f, -10.0f);
b2World World(Gravity);
b2CircleShape* STDShape;
b2PolygonShape* W1;
b2PolygonShape* W2;
TextFont* NewFont;
SDL_Color* NewColor = new SDL_Color;
SDL_Color* NewColorBG = new SDL_Color;

int CamX = 0;
int CamY = 0;
SDL_Event* Ev;

int StartTime = GetTickCount();
int Now = GetTickCount();
int Delta = 0;

SYNCPATH SYNCMODE = IMAGE;

bool FPSCheck(float Step)
{
	bool Ret = false;
	Now = GetTickCount();
	Delta = Now - StartTime;

	if (Delta >= Step * 1000)
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


void ModColors()
{
	int Mode = RndGen(3);
	switch (Mode)
	{

	case 1:
		if (NewColor->b < 256)
		{
			NewColor->b += RndGen(20);
		}
		else
		{
			NewColor->b = 0;
		}
		break;
	case 2:
		if (NewColor->g < 256)
		{
			NewColor->g += RndGen(20);
		}
		else
		{
			NewColor->g = 0;
		}
		break;
	case 3:
		if (NewColor->r < 256)
		{
			NewColor->r += RndGen(20);
		}
		else
		{
			NewColor->r = 0;
		}
		break;
	default:
		break;
	}
}

void Init()
{
	
	NewFont = new TextFont("font.ttf");
	NewFont->PointSize = 30;
	NewColor->a = 0;
	NewColor->b = 255;
	NewColor->g = 0;
	NewColor->r = 0;
	NewColorBG->a = 0;
	NewColorBG->b = 0;
	NewColorBG->g = 0;
	NewColorBG->r = 255;

	mainEngine.InitPhysics();
	mainEngine.InitObjects(0, 0, 1, 0);
	mainEngine.InitGraphics(WWIDTH, WHEIGHT, "Test #002.");

	mainEngine.Graphics->Start();
	mainEngine.Graphics->SetTextMaximumTime(K);
	mainEngine.Physics->AddWorld(&World);
	STDShape = new b2CircleShape;
	STDShape->m_p.Set(0.0f, 0.0f);
	STDShape->m_radius = 0.1f;
	W1 = new b2PolygonShape;
	W1->SetAsBox(10.f, 5.f);
	W2 = new b2PolygonShape;
	W2->SetAsBox(5.f, 10.f);
	b2BodyDef* BodyDefinitionBall = new b2BodyDef;
	BodyDefinitionBall->type = b2_dynamicBody;
	b2FixtureDef* FixtureDefBall = new b2FixtureDef;
	FixtureDefBall->restitution = 1.1f;
	FixtureDefBall->friction = 0.5f;
	FixtureDefBall->shape = STDShape;
	float Rnd1 = (float)RndGen(9)+1.f;
	float Rnd2 = (float)RndGen(9) + 1.f;
	for (int i = 0; i < BallCount; i++)
	{
		BodyDefinitionBall->position.Set(Rnd1, Rnd2);
		Rnd1 = (float)RndGen(9) + 1.f;
		Rnd2 = (float)RndGen(9) + 1.f;
		Balls.at(i) = new ObjectBASE(&World, mainEngine.getObjects()->ManagerDB.at(0), mainEngine.getEventingEngine(), true, true);
		Balls.at(i)->CreateBody(BodyDefinitionBall);
		Balls.at(i)->CreateFixture(FixtureDefBall);
		Balls.at(i)->SetImageSource("Ball.png");
		Balls.at(i)->ForceLocalFactor = true;
		Balls.at(i)->SyncFactor = K;
		Balls.at(i)->SetTextFont(NewFont);
		Balls.at(i)->SetTextColorFG(NewColor);
		Balls.at(i)->SetTextColorBG(NewColorBG);
		Balls.at(i)->SetTextContent(string(1, char(RndGen(255))));

	}
	b2BodyDef* BodyDefinitionWall = new b2BodyDef;
	BodyDefinitionWall->type = b2_kinematicBody;
	b2FixtureDef* FixtureDefWall = new b2FixtureDef;
	FixtureDefWall->restitution = 1.f;
	for (int j = 0; j < WallCount; j++)
	{
		Walls.at(j) = new ObjectBASE(&World, mainEngine.getObjects()->ManagerDB.at(0), mainEngine.getEventingEngine(), true, true);
		Walls.at(j)->SetImageSource("Wall.png");
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
	mainEngine.getObjects()->ManagerDB.at(0)->PushChanges();
}


void RenderPhysics()
{
	float Step = 1.f / 70.f;
	World.Step(Step, 10, 3);


}

void RenderGraphics()
{
	ModColors();
	
	mainEngine.Graphics->DrawerGL->SyncObjects(true, SYNCMODE);
	

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
	else if (A[SDL_SCANCODE_1])
	{
		SYNCMODE = ALL;
	}
	else if (A[SDL_SCANCODE_2])
	{
		SYNCMODE = IMAGE;
	}
	else if (A[SDL_SCANCODE_3])
	{
		SYNCMODE = TEXT;
	}
	mainEngine.Graphics->DrawerGL->SetView(CamX, CamY);

}

int main(int argc, char** argv)
{
	Init();
	bool Close = false;
	while (Close == false)
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