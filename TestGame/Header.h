#include "GameEngine.h"

const static GLfloat colors[12][3] =		// Rainbow Of Colors
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
	unsigned int col;
	EngineFireEffect(int ParticleCount, ObjDBManager<EffectElement>* EffectManager, string Path) :EffectBASE(EffectManager, ParticleCount, Path)
	{
		xspeed = 200.f;
		yspeed = 200.f;
		col = 2;
	}

	virtual void Init()
	{
		for (int loop = 0; loop < ParticleCount; loop++)				// Initials All The Textures
		{
			ParticleArray[loop].X = 0.f;
			ParticleArray[loop].Y = 0.f;
			ParticleArray[loop].Angle = 0.f;
			ParticleArray[loop].Active = true;								// Make All The Particles Active
			ParticleArray[loop].Fade = 1.0f;								// Give All The Particles Full Life
			ParticleArray[loop].Life = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Speed
			ParticleArray[loop].R = colors[loop*(12 / ParticleCount)][0];	// Select Red Rainbow Color
			ParticleArray[loop].G = colors[loop*(12 / ParticleCount)][1];	// Select Red Rainbow Color
			ParticleArray[loop].B = colors[loop*(12 / ParticleCount)][2];	// Select Red Rainbow Color
			ParticleArray[loop].SpeedX = float((rand() % 50) - 26.0f)*100.0f;		// Random Speed On X Axis
			ParticleArray[loop].SpeedY = float((rand() % 50) - 25.0f)*100.0f;		// Random Speed On Y Axis
			//ParticleArray[loop].zi = float((rand() % 50) - 25.0f)*10.0f;		// Random Speed On Z Axis
			ParticleArray[loop].GravityX = 0.0f;									// Set Horizontal Pull To Zero
			ParticleArray[loop].GravityY = -0.8f;								// Set Vertical Pull Downward
			//ParticleArray[loop].zg = 0.0f;								// Set Pull On Z Axis To Zero
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
				ParticleArray[loop].X += ParticleArray[loop].SpeedX / (slowdown * 1000);// Move On The X Axis By X Speed
				ParticleArray[loop].Y += ParticleArray[loop].SpeedY / (slowdown * 1000);// Move On The Y Axis By Y Speed
				//ParticleArray[loop].Z += ParticleArray[loop].zi / (slowdown * 1000);// Move On The Z Axis By Z Speed

				ParticleArray[loop].SpeedX += ParticleArray[loop].GravityX;			// Take Pull On X Axis Into Account
				ParticleArray[loop].SpeedY += ParticleArray[loop].GravityY;			// Take Pull On Y Axis Into Account
				//ParticleArray[loop].zi += ParticleArray[loop].zg;			// Take Pull On Z Axis Into Account
				ParticleArray[loop].Fade -= ParticleArray[loop].Life;		// Reduce Particles Life By 'Fade'
				srand(SDL_GetTicks());
				col = rand() % 3;
				if (ParticleArray[loop].Fade < 0.0f)					// If ParticleArray Is Burned Out
				{
					ParticleArray[loop].Fade = 1.0f;					// Give It New Life
					ParticleArray[loop].Life = float(rand() % 100) / 1000.0f + 0.003f;	// Random Fade Value
					ParticleArray[loop].X = 0.0f;						// Center On X Axis
					ParticleArray[loop].Y = 0.0f;						// Center On Y Axis
					//ParticleArray[loop].z = 0.0f;						// Center On Z Axis
					ParticleArray[loop].SpeedX = xspeed + float((rand() % 60) - 32.0f);	// X Axis Speed And Direction
					ParticleArray[loop].SpeedY = yspeed + float((rand() % 60) - 30.0f);	// Y Axis Speed And Direction
					//ParticleArray[loop].zi = float((rand() % 60) - 30.0f);	// Z Axis Speed And Direction
					srand(SDL_GetTicks());
					col = rand() % 3;
					ParticleArray[loop].R = colors[col][0];			// Select Red From Color Table
					srand(SDL_GetTicks());
					col = rand() % 3;
					ParticleArray[loop].G = colors[col][1];			// Select Green From Color Table
					srand(SDL_GetTicks());
					col = rand() % 3;
					ParticleArray[loop].B = colors[col][2];			// Select Blue From Color Table
				}
			}
		}
	}
};