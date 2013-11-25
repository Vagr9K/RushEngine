#include "GameEngine.h"



int main(int argc, char** argv)
{
	b2Vec2 Gravity(0,10.0);
	
	b2World MainWorld(Gravity);
	GameEngine* mainEngine = new GameEngine;
	mainEngine->StartGraphics(300, 400, 10, "Title");
	mainEngine->InitObjects(1, 0, 1, 0);
	mainEngine->InitPhysics();
	mainEngine->Physics->AddWorld(&MainWorld);
	
	IMG* Image;
	TXT* Text;
	b2Filter* Filter;
	Object* Obj;

	for (int i = 0; i < 1000;i++)
	{
		Image = new IMG(10, 10, 10, 10, 32.5, "imageasdhasyfdisafgsuadfkuvakdf.png");
		Text = new TXT(12, 12, 12, 12, 12, "faksdgfuagkfaadfsadfadadufguuyfhukalsy.jpg");
		Filter = new b2Filter;
		Filter->categoryBits = 12;
		b2PolygonShape Pol;
		Pol.SetAsBox(12.7f, 12.7f);



		Obj = new Object(mainEngine, 0,1);
		Obj->InitObjElement();
		Obj->AddImage(Image);
		Obj->AddText(Text);
		Obj->BodyDefinition = new b2BodyDef;
		Obj->BodyDefinition->active = true;
		Obj->BodyDefinition->allowSleep = true;
		Obj->BodyDefinition->angle = 32.9f;
		Obj->BodyDefinition->angularDamping = 12.0f;
		Obj->BodyDefinition->awake = true;
		Obj->BodyDefinition->bullet = true;
		Obj->BodyDefinition->type = b2_dynamicBody;
		Obj->CreateBody();
		Obj->AddObjElementToManager();
		Obj->InitFixtureDefinition();
		Obj->FixtureDefinition->density = 12.4f;
		Obj->FixtureDefinition->filter = *Filter;
		Obj->FixtureDefinition->friction = 12;
		Obj->FixtureDefinition->isSensor = false;
		Obj->FixtureDefinition->restitution = 12.0f;
		Obj->FixtureDefinition->shape = &Pol;
		Obj->CreateFixture();
		Obj->AddObjElementToManager();
		Obj->PushManagerChanges();

	}

	SDL_Event e;
	 bool Die = false;
	 while (Die == false)
	 {
		 mainEngine->Graphics->BlackInit();
		 if(SDL_PollEvent(&e) != 0) 
		 if (e.type==SDL_QUIT)
		 {
			 Die = true;
			
		 }
		 mainEngine->BlackInitGraphics();
		
	 }
	 mainEngine->StopGraphics();
	
	return 0;
}