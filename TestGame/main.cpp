#include "GameEngine.h"
#include <cstdlib>
#include <ctime>
#include <iostream> 

#include <string>
#include <sstream>

#include "Header.h"

using namespace std;

#define WHEIGHT 900
#define WWIDTH 1000


#define  BallCount  100
#define  WallCount  4

#define  K 100


GameEngine mainEngine;

string PointerToEngine;

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

ObjectSyncMode SYNCMODE = IMAGE;

FPSTest* Tester;


EngineFireEffect* EffectTest;
Button* TestButton;

AudioMusic* Music;
AudioEffect* Eff;



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
	stringstream SS;
	SS << RushEngineInfo.GamePointer;
	PointerToEngine = SS.str();


	Tester = new FPSTest;

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

	mainEngine.InitObjects(1, 1, 1, 1);
	mainEngine.InitGraphics(WWIDTH, WHEIGHT, "Test #004.");
	mainEngine.Graphics->Start();
	mainEngine.Graphics->SetTextMaximumTime(K + 2);
	mainEngine.Graphics->DrawerGL->CacheImage("Ball.png");
	mainEngine.Graphics->DrawerGL->CacheImage("Wall.png");

	mainEngine.Physics->AddWorld(&World);

	EffectTest = new EngineFireEffect(250, mainEngine.getObjects()->getEffectManager(0), "Particle.png");
	mainEngine.getObjects()->getEffectManager(0)->PushChanges();

	TestButton = new Button(mainEngine.getObjects()->getInterfaceManager(0), mainEngine.Eventing);
	mainEngine.getObjects()->getInterfaceManager(0)->PushChanges();


	Music = new AudioMusic("Music.wav");
	Music->Play(0);

	Eff = new AudioEffect("Effect.wav", 6.1);

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
	FixtureDefBall->friction = 0.1f;
	FixtureDefBall->shape = STDShape;
	float Rnd1 = (float)RndGen(9)+1.f;
	float Rnd2 = (float)RndGen(9) + 1.f;
	for (int i = 0; i < BallCount; i++)
	{
		BodyDefinitionBall->position.Set(Rnd1, Rnd2);
		Rnd1 = (float)RndGen(9) + 1.f;
		Rnd2 = (float)RndGen(9) + 1.f;
		Balls.at(i) = new ObjectBASE(&World, mainEngine.getObjects()->getObjectManager(0), mainEngine.Eventing, true, true);
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
		Walls.at(j) = new ObjectBASE(&World, mainEngine.getObjects()->getObjectManager(0), mainEngine.Eventing, true, true);
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

	BackgroundBASE* BgkWood = new BackgroundBASE(mainEngine.getObjects()->getBackgroundManager(), mainEngine.Eventing, true);
	IMG* Wood = new IMG;
	Wood->h = 1000;
	Wood->w = 1100;
	Wood->Source = "Wood.png";
	Wood->x = 500;
	Wood->y = 450;
	Wood->Angle = 0.f;
	BgkWood->AddImage(Wood);

	mainEngine.getObjects()->getObjectManager(0)->PushChanges();
	mainEngine.getObjects()->getBackgroundManager()->PushChanges();
}


void RenderPhysics()
{
	float Step = 1.f / 60.f;
	World.Step(Step, 8, 3);
	b2Vec2 Pos = Balls.at(5)->Body->GetPosition();
	EffectTest->X =WWIDTH - Pos.x*K;
	EffectTest->Y =WHEIGHT -Pos.y*K;
}

void RenderGraphics()
{
	ModColors();
	mainEngine.Graphics->DrawerGL->SyncAll(false);
	Tester->PushFrame();
	double FPS = Tester->getFPS();
	double Diff = Tester->getLastDiff();
	if (true)
	{
		string NewTitle = "FPS : " + to_string(FPS) + " HZ.";
		mainEngine.Graphics->DrawerGL->AddToBuffer(100, 50, 30, 200, NewFont, NewTitle, BLENDED, *NewColor, *NewColorBG);
		
	}
	mainEngine.Eventing->Input->Mouse->Refresh();
	string Pos = to_string(mainEngine.Eventing->Input->Mouse->Status.X) + " : " + to_string(mainEngine.Eventing->Input->Mouse->Status.Y);
	mainEngine.Graphics->DrawerGL->AddToBuffer(100, 100, 30, 200, NewFont, Pos, BLENDED, *NewColor, *NewColorBG);

	mainEngine.Graphics->DrawerGL->AddToBuffer(100, 400, 30, 200, NewFont, PointerToEngine, BLENDED, *NewColor, *NewColorBG);
	mainEngine.Graphics->DrawerGL->PushBuffer();

	Eff->Play(0);
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
	mainEngine.Graphics->DrawerGL->SetView(CamX, CamY);

}

int main(int argc, char** argv)
{
	Init();
	bool Close = false;
	while (Close == false)
	{
		if (mainEngine.Eventing->GlobalEvent.type == SDL_QUIT)
		{
			Close = true;
		}
		RenderPhysics();

		RenderGraphics();


		RenderCamera();
		
	}


	return 0;
}