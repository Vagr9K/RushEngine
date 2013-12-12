#include "GameEngine.h"
#include <cstdlib>
#include <ctime>

#define WHEIGHT 900
#define WWIDTH 680




int main(int argc, char** argv)
{
	b2Vec2 Gravity(0,-10.0);
	
	b2World MainWorld(Gravity);
	GameEngine* mainEngine = new GameEngine;
	mainEngine->InitGraphics(WWIDTH, WHEIGHT, 2, "Very stupid physics test...");
	mainEngine->Graphics->Start();
	mainEngine->Graphics->InitGL();

	mainEngine->InitObjects(0, 0, 1, 0);
	mainEngine->InitPhysics();
	mainEngine->Physics->AddWorld(&MainWorld);



	
	SDL_Event e;

	
	int StartTime = GetTickCount();
	int Now = GetTickCount();
	int Delta=0;
	const int FPS = 60;
	 bool Die = false;
	 Object Ball(mainEngine, 0,0);
	 Ball.BodyDefinition = new b2BodyDef;
	 Ball.BodyDefinition->type = b2_dynamicBody;
	 Ball.BodyDefinition->position.Set(5, 8);
	 Ball.CreateBody();
	 Ball.FixtureDefinition = new b2FixtureDef;
	 Ball.FixtureDefinition->restitution = 1.0f;
	 b2Vec2 Vert1[3]; 
	 Vert1[0].Set(0, 0);
	 Vert1[1].Set(1, 0);
	 Vert1[2].Set(0.5, 1);
	 b2PolygonShape Shape;
	 Shape.Set(Vert1, 3);
	 
	 Ball.FixtureDefinition->shape =&Shape;
	 Ball.CreateFixture();


	 b2BodyDef groundBodyDef;
	 groundBodyDef.position.Set(0.0f, -10.0f);
	 b2Body* groundBody = MainWorld.CreateBody(&groundBodyDef);
	 b2PolygonShape groundBox;
	 groundBox.SetAsBox(50.0f, 10.0f);
	 groundBody->CreateFixture(&groundBox, 0.0f);

	 float32 Hz = 1.0f/30.0f;
	 MainWorld.Step(Hz, 10, 8);

	 b2Vec2 Pos1;
	 b2Vec2 Pos2;
	 TextFont FontofText("font.ttf");
	 FontofText.PointSize = 50;

	 SDL_Color Foreground;
	 Foreground.a = 234;
	 Foreground.b = 34;
	 Foreground.g = 56;
	 Foreground.r = 23;

	 SDL_Color Back;
	 Back.a = 23;
	 Back.b = 234;
	 Back.g = 23;
	 Back.r = 245;
	 string Text;
	 int Angle1 = 0;
	 int VX = 0;
	 int VY = 0;
	while (Die == false)
	 {
		Now = GetTickCount();
		Delta = Now - StartTime;
		if (Delta>=(Hz))
		{
			StartTime = GetTickCount();
			if (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
			{
				Die = true;

			}
			MainWorld.Step(Hz, 10, 8);
			Pos1 = Ball.Body->GetPosition();
			float32 Angle = Ball.Body->GetAngle();
			Text = to_string(static_cast<long long>(Pos1.x * 100)) + " " + to_string(static_cast<long long>(Pos1.y * 100));
			Angle1++;

			const Uint8* A = SDL_GetKeyboardState(NULL);
			if (A[SDL_SCANCODE_RIGHT])
			{
				VX+=40;
			} 
			else if (A[SDL_SCANCODE_LEFT])
			{
				VX-=40;
			}
			else if (A[SDL_SCANCODE_UP])
			{
				VY+=40;
			}
			else if (A[SDL_SCANCODE_DOWN])
			{
				VY=VY-40;
			}
			
			mainEngine->Graphics->DrawerGL->StartBuffer();
			
			
			mainEngine->Graphics->DrawerGL->AddToBuffer(Pos1.x*100, Pos1.y*100, 30, 30, "images/BlackInit.png", Angle);
			mainEngine->Graphics->DrawerGL->AddToBuffer((Pos1.x*100+50),Pos1.y*100, 30, 30, "images/image.png", Angle1);
			
			mainEngine->Graphics->DrawerGL->SetViewPort(VX, VY, WHEIGHT, WWIDTH);
			mainEngine->Graphics->DrawerGL->PushBuffer();
			
			

		}
		
	 }

	 mainEngine->DeleteGraphics();
	
	return 0;
}
