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

	struct ParticleData
	{
		float SpeedX;
		float SpeedY;
		float FadeSpeed;
		ParticleData()
		{
			
		}
		void ReRandom(float RandomAspectSpeed, float RandomAspectFading)
		{
			
			SpeedX = (static_cast<float>(rand() % 1000) / 1000.f - 0.5f) * RandomAspectSpeed;
			SpeedY = (static_cast<float>(rand() % 1000) / 1000.f - 0.5f) * RandomAspectSpeed;
			FadeSpeed = static_cast<float>(rand() % 1000) / 100000 * RandomAspectFading;
		}
	};
	struct GravityData
	{
		float X;
		float Y;
		GravityData()
		{
			X = 0.f;
			Y = 0.f;
		}
	};
	struct DeadZoneData
	{
		float MinX;
		float MaxX;
		float MinY;
		float MaxY;
		bool Active;
		DeadZoneData()
		{
			Active = false;
		}
	};
	struct ColorData
	{
		float R, G, B, Fade;
		ColorData()
		{
			R = 1.f;
			G = 1.f;
			B = 1.f;
			Fade = 1.f;
		}
	};
	struct SpeedData
	{
		float X, Y;
		SpeedData()
		{
			X = 0.f;
			Y = 0.f;
		}
	};

	ParticleData* PData;
	void InitParticle(int ID)
	{
		
		ParticleArray[ID].H = 4.f;
		ParticleArray[ID].W = 4.f;
		ParticleArray[ID].X = X * PixelMeter;
		ParticleArray[ID].Y = Y * PixelMeter;
		ParticleArray[ID].R = Color.R + static_cast<float>(rand() % 100) / 100 - 0.5f;
		if (ParticleArray[ID].R > 1.f)
			ParticleArray[ID].R = 1.f;
		ParticleArray[ID].G = Color.G + static_cast<float>(rand() % 100) / 100 - 0.5f;
		if (ParticleArray[ID].G > 1.f)
			ParticleArray[ID].G = 1.f;
		ParticleArray[ID].B = Color.B + static_cast<float>(rand() % 100) / 100 - 0.5f;
		if (ParticleArray[ID].B > 1.f)
			ParticleArray[ID].B = 1.f;
		ParticleArray[ID].Fade = Color.Fade;
		ParticleArray[ID].Active = true;
		PData[ID].ReRandom(RandomAspectSpeed, RandomAspectFading);
		PData[ID].SpeedX += Speed.X;
		PData[ID].SpeedY += Speed.Y;
	}
protected:
	virtual void Init()
	{
		PData = new ParticleData[ParticleCount];
		for (int i = 0; i < ParticleCount; i++)
		{
			InitParticle(i);
		}
	}

	virtual void RefreshPosition()
	{
		for (int i = 0; i < ParticleCount;i++)
		{
			ParticleArray[i].Fade -= PData[i].FadeSpeed;
			if (ParticleArray[i].Fade < 0.f)
			{
				InitParticle(i);
			}
			else
			{
				ParticleArray[i].X += (Gravity.X + PData[i].SpeedX) * PixelMeter / static_cast<float>(RenderPS);
				ParticleArray[i].Y += (Gravity.Y + PData[i].SpeedY) * PixelMeter / static_cast<float>(RenderPS);
				if (DeadZones.Active)
				{
					if (ParticleArray[i].X < DeadZones.MinX || ParticleArray[i].X > DeadZones.MaxX)
						InitParticle(i);
					else if (ParticleArray[i].Y < DeadZones.MinY || ParticleArray[i].Y > DeadZones.MaxY)
						InitParticle(i);
				}
			}
			
			
		}
	}
public:
	float X, Y;
	float PixelMeter;
	int RenderPS;
	float RandomAspectSpeed;
	float RandomAspectFading;
	GravityData Gravity;
	ColorData Color;
	SpeedData Speed;
	DeadZoneData DeadZones;
	void SetData(float GravityX,float GravityY,float SpeedX,float SpeedY,float ZeroX,float ZeroY)
	{
		this->Gravity.X = GravityX;
		this->Gravity.Y = GravityY;
		this->Speed.X = SpeedX;
		this->Speed.Y = SpeedY;
		this->X = ZeroX;
		this->Y = ZeroY;
	}
	FlareEffect(int LayerID, int ParticleCount, float PixelMeter = 1.0f, int RenderPS = 1) : Effect(LayerID, ParticleCount, "Effects/Flare.png")
	{
		this->PixelMeter = PixelMeter;
		this->RenderPS = RenderPS;
		SetBlendMode(BLEND);
		RandomAspectSpeed = 1.f;
		RandomAspectFading = 1.f;
	}
};

class SmokeEffect : public Effect
{

	struct ParticleData
	{
		float SpeedX;
		float SpeedY;
		float FadeSpeed;
		ParticleData()
		{

		}
		void ReRandom(float RandomAspectSpeed, float RandomAspectFading)
		{

			SpeedX = (static_cast<float>(rand() % 1000) / 1000.f - 0.5f) * RandomAspectSpeed;
			SpeedY = (static_cast<float>(rand() % 1000) / 1000.f - 0.5f) * RandomAspectSpeed;
			FadeSpeed = static_cast<float>(rand() % 1000) / 100000 * RandomAspectFading;
		}
	};
	struct GravityData
	{
		float X;
		float Y;
		GravityData()
		{
			X = 0.f;
			Y = 0.f;
		}
	};
	struct DeadZoneData
	{
		float MinX;
		float MaxX;
		float MinY;
		float MaxY;
		bool Active;
		DeadZoneData()
		{
			Active = false;
		}
	};
	struct ColorData
	{
		float R, G, B, Fade;
		ColorData()
		{
			R = 1.f;
			G = 1.f;
			B = 1.f;
			Fade = 1.f;
		}
	};
	struct SpeedData
	{
		float X, Y;
		SpeedData()
		{
			X = 0.f;
			Y = 0.f;
		}
	};

	ParticleData* PData;
	void InitParticle(int ID)
	{

		ParticleArray[ID].H = 32.f;
		ParticleArray[ID].W = 32.f;
		ParticleArray[ID].X = X * PixelMeter;
		ParticleArray[ID].Y = Y * PixelMeter;
		ParticleArray[ID].R = Color.R + static_cast<float>(rand() % 1) / 100 - 0.005f;
		if (ParticleArray[ID].R > 1.f)
			ParticleArray[ID].R = 1.f;
		ParticleArray[ID].G = Color.G + static_cast<float>(rand() % 1) / 100 - 0.005f;
		if (ParticleArray[ID].G > 1.f)
			ParticleArray[ID].G = 1.f;
		ParticleArray[ID].B = Color.B + static_cast<float>(rand() % 1) / 100 - 0.005f;
		if (ParticleArray[ID].B > 1.f)
			ParticleArray[ID].B = 1.f;
		ParticleArray[ID].Fade = Color.Fade;
		ParticleArray[ID].Angle = static_cast<float>(rand() % 360);
		ParticleArray[ID].Active = true;
		PData[ID].ReRandom(RandomAspectSpeed, RandomAspectFading);
		PData[ID].SpeedX += Speed.X;
		PData[ID].SpeedY += Speed.Y;
	}
protected:
	virtual void Init()
	{
		PData = new ParticleData[ParticleCount];
		for (int i = 0; i < ParticleCount; i++)
		{
			InitParticle(i);
		}
	}

	virtual void RefreshPosition()
	{
		for (int i = 0; i < ParticleCount; i++)
		{
			ParticleArray[i].Fade -= PData[i].FadeSpeed;
			if (ParticleArray[i].Fade < 0.f)
			{
				InitParticle(i);
			}
			else
			{
				ParticleArray[i].X += (Gravity.X + PData[i].SpeedX) * PixelMeter / static_cast<float>(RenderPS);
				ParticleArray[i].Y += (Gravity.Y + PData[i].SpeedY) * PixelMeter / static_cast<float>(RenderPS);
				if (DeadZones.Active)
				{
					if (ParticleArray[i].X < DeadZones.MinX || ParticleArray[i].X > DeadZones.MaxX)
						InitParticle(i);
					else if (ParticleArray[i].Y < DeadZones.MinY || ParticleArray[i].Y > DeadZones.MaxY)
						InitParticle(i);
				}
			}


		}
	}
public:
	float X, Y;
	float PixelMeter;
	int RenderPS;
	float RandomAspectSpeed;
	float RandomAspectFading;
	GravityData Gravity;
	ColorData Color;
	SpeedData Speed;
	DeadZoneData DeadZones;
	void SetData(float GravityX, float GravityY, float SpeedX, float SpeedY, float ZeroX, float ZeroY)
	{
		this->Gravity.X = GravityX;
		this->Gravity.Y = GravityY;
		this->Speed.X = SpeedX;
		this->Speed.Y = SpeedY;
		this->X = ZeroX;
		this->Y = ZeroY;
	}
	SmokeEffect(int LayerID, int ParticleCount, float PixelMeter = 1.0f, int RenderPS = 1) : Effect(LayerID, ParticleCount, "Effects/Smoke.png")
	{
		this->PixelMeter = PixelMeter;
		this->RenderPS = RenderPS;
		RandomAspectSpeed = 0.25f;
		RandomAspectFading = 1.f;
		this->SetBlendMode(BLEND);
	}
};