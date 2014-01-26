#include "GameEngine.h"

const static GLfloat colors[12][3] =		
{
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};
class EngineFireEffect : public Effect
{
	float slowdown;

public:
	float xspeed;
	float yspeed;
	float X, Y;
	unsigned int col;
	EngineFireEffect(int ParticleCount, ObjDBManager<EffectElement>* EffectManager, string Path) :Effect(EffectManager, ParticleCount, Path)
	{
		xspeed = 0.f;
		yspeed = 2000.f;
		slowdown = 2.f;
		X = 0.f;
		Y = 0.f;
	}

	virtual void Init()
	{
		for (int loop = 0; loop < ParticleCount; loop++)				
		{
			ParticleArray[loop].X = X;
			ParticleArray[loop].Y = Y;
			ParticleArray[loop].Angle = 0.f;
			ParticleArray[loop].Active = true;								
			ParticleArray[loop].Fade = 1.0f;								
			ParticleArray[loop].Life = float(rand() % 1000) / 1000.0f + 0.003f;	
			ParticleArray[loop].R = colors[loop*(12 / ParticleCount)][0];	
			ParticleArray[loop].G = colors[loop*(12 / ParticleCount)][1];	
			ParticleArray[loop].B = colors[loop*(12 / ParticleCount)][2];	
			ParticleArray[loop].SpeedX = float((rand() % 50) - 26.0f)*100.0f;		
			ParticleArray[loop].SpeedY = float((rand() % 50) - 25.0f)*100.0f;		
			ParticleArray[loop].GravityX = 0.0f;									
			ParticleArray[loop].GravityY = 0.98f;								
			ParticleArray[loop].H = 10.f;
			ParticleArray[loop].W = 10.f;
		}
	}

	virtual void RefreshPosition()
	{
		for (int loop = 0; loop < ParticleCount; loop++)
		{
			if (ParticleArray[loop].Active)
			{
				ParticleArray[loop].X += ParticleArray[loop].SpeedX / (slowdown * 1000);
				ParticleArray[loop].Y += ParticleArray[loop].SpeedY / (slowdown * 1000);
				ParticleArray[loop].SpeedX += ParticleArray[loop].GravityX;			
				ParticleArray[loop].SpeedY += ParticleArray[loop].GravityY;			
				ParticleArray[loop].Fade -= ParticleArray[loop].Life;	
				srand(SDL_GetTicks());
				col = rand() % 3;
				if (ParticleArray[loop].Fade < 0.0f)					
				{
					ParticleArray[loop].Fade = 1.0f;				
					ParticleArray[loop].Life = float(rand() % 100) / 1000.0f + 0.003f;	
					ParticleArray[loop].X = X;						
					ParticleArray[loop].Y = Y;						
					ParticleArray[loop].SpeedX = xspeed + float((rand() % 600) - 320.0f);	
					ParticleArray[loop].SpeedY = yspeed + float((rand() % 600) - 300.0f);	
					ParticleArray[loop].R = colors[col][0];
					ParticleArray[loop].G = colors[col][1];	
					ParticleArray[loop].B = colors[col][2];			
				}
			}
		}
	}
};

class Button : public Interface
{
	string Path1;
	string Path2;
	void SetPath(int Num)
	{
		if (Num == 1)
		{
			InterElement->Image->Source = Path1;
		}
		else
		{
			InterElement->Image->Source = Path2;
		}
	}
public:

	Button(ObjDBManager<InterfaceElement>* ManagerDB, EventingEngine* EventSystem) :Interface(ManagerDB, EventSystem)
	{
		Path1 = "Button1.png";
		Path2 = "Button2.png";
	}
	virtual void Init()
	{
		InterElement->ImageExists = true; 
		InterElement->Image = new IMG(50.f, 150.f, 64.f, 64.f, 12.f, "Button1.png");
	}
	virtual void OnHover()
	{
		SetPath(2);
	}
	virtual void OnNULL()
	{
		SetPath(1);
	}
};