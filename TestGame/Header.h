#include "GameEngine.h"
#include <random>

const static GLfloat colors[12][3] =		
{
	{ 1.0f, 0.5f, 0.5f }, { 1.0f, 0.75f, 0.5f }, { 1.0f, 1.0f, 0.5f }, { 0.75f, 1.0f, 0.5f },
	{ 0.5f, 1.0f, 0.5f }, { 0.5f, 1.0f, 0.75f }, { 0.5f, 1.0f, 1.0f }, { 0.5f, 0.75f, 1.0f },
	{ 0.5f, 0.5f, 1.0f }, { 0.75f, 0.5f, 1.0f }, { 1.0f, 0.5f, 1.0f }, { 1.0f, 0.5f, 0.75f }
};
class ParticleDATA 
{
public:
	
	float Life;
	float SpeedX;
	float SpeedY;
	float GravityX;
	float GravityY;

};
class EngineFireEffect : public Effect
{
	float slowdown;

public:
	float xspeed;
	float yspeed;
	float X, Y;
	unsigned int col;
	ParticleDATA* ParticleData;
	EngineFireEffect(int ParticleCount, ObjDBManager<EffectElement>* EffectManager, string Path) :Effect(EffectManager, ParticleCount, Path)
	{
		ParticleData = new ParticleDATA[ParticleCount];
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
			ParticleData[loop].Life = float(rand() % 1000) / 1000.0f + 0.003f;	
			ParticleArray[loop].R = colors[loop*(12 / ParticleCount)][0];	
			ParticleArray[loop].G = colors[loop*(12 / ParticleCount)][1];	
			ParticleArray[loop].B = colors[loop*(12 / ParticleCount)][2];	
			ParticleData[loop].SpeedX = float((rand() % 50) - 26.0f)*100.0f;
			ParticleData[loop].SpeedY = float((rand() % 50) - 25.0f)*100.0f;
			ParticleData[loop].GravityX = 0.0f;
			ParticleData[loop].GravityY = 0.98f;
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
				ParticleArray[loop].X += ParticleData[loop].SpeedX / (slowdown * 1000);
				ParticleArray[loop].Y += ParticleData[loop].SpeedY / (slowdown * 1000);
				ParticleData[loop].SpeedX += ParticleData[loop].GravityX;
				ParticleData[loop].SpeedY += ParticleData[loop].GravityY;
				ParticleArray[loop].Fade -= ParticleData[loop].Life;
				srand(SDL_GetTicks());
				col = rand() % 3;
				if (ParticleArray[loop].Fade < 0.0f)					
				{
					ParticleArray[loop].Fade = 1.0f;				
					ParticleData[loop].Life = float(rand() % 100) / 1000.0f + 0.003f;
					ParticleArray[loop].X = X;						
					ParticleArray[loop].Y = Y;						
					ParticleData[loop].SpeedX = xspeed + float((rand() % 600) - 320.0f);
					ParticleData[loop].SpeedY = yspeed + float((rand() % 600) - 300.0f);
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
	virtual void OnClick()
	{
		RushEngineInfo.GamePointer->Graphics->ShowMessageBox("You have pressed the button.", "The button on screen was pressed by you!");
	}

};


class FlareEffect : public Effect
{
	 void InitParticle(int ID)
	{
		ParticleArray[ID].H = 4.f;
		ParticleArray[ID].W = 4.f;
		ParticleArray[ID].X = ZeroX;
		ParticleArray[ID].Y = ZeroY;
		ParticleArray[ID].R = R;
		ParticleArray[ID].G = G;
		ParticleArray[ID].B = B;
		ParticleArray[ID].Fade = Fade;
		ParticleArray[ID].Active = true;
	}
protected:
	virtual void Init()
	{
		for (int i = 0; i < ParticleCount; i++)
		{
			InitParticle(i);
		}
	}

	virtual void RefreshPosition()
	{
		srand(SDL_GetTicks());
		
		float SpX = SpeedX + GravityX;
		float SpY = SpeedY + GravityY;
		for (int i = 0; i < ParticleCount;i++)
		{
			
			ParticleArray[i].Fade -= 0.01f;
			if (ParticleArray[i].Fade < 0.f)
			{
				InitParticle(i);
			}
			
			
			
		}
	}
public:
	float GravityX, GravityY, SpeedX, SpeedY, ZeroX, ZeroY;
	float R, G, B, Fade;
	void SetData(float GravityX,float GravityY,float SpeedX,float SpeedY,float ZeroX,float ZeroY)
	{
		this->GravityX = GravityX;
		this->GravityY = GravityY;
		this->SpeedX = SpeedX;
		this->SpeedY = SpeedY;
		this->ZeroX = ZeroX;
		this->ZeroY = ZeroY;
	}
	FlareEffect(int LayerID, int ParticleCount) : Effect(LayerID, ParticleCount, "assets/Effects/Flare.png")
	{

	}
};