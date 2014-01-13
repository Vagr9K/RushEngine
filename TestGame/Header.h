#include "GameEngine.h"

const static GLfloat colors[12][3] =		
{
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};
class EngineFireEffect : public EffectBASE
{
	float slowdown = 2.f;

public:
	float xspeed;
	float yspeed;
	float X=0.f, Y=0.f;
	unsigned int col;
	EngineFireEffect(int ParticleCount, ObjDBManager<EffectElement>* EffectManager, string Path) :EffectBASE(EffectManager, ParticleCount, Path)
	{
		xspeed = 0.f;
		yspeed = 2000.f;
		
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