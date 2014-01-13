#include "ObjectManager.h"

class EffectBASE
{
	bool Inited;
protected:
	EffectElement* EffElement;
	ObjDBManager<EffectElement>* EffectManager;
protected:
	int FrameNumber;
	int ParticleCount;
protected:
	Particle* ParticleArray;
	void AddToManager()
	{
		EffectManager->AddToCreate(EffElement);
	}

	void DeleteFromManager()
	{
		EffectManager->AddToCreate(EffElement);
	}

	virtual void Init() = 0;

	virtual void RefreshPosition() = 0;


public:
	EffectBASE(ObjDBManager<EffectElement>* EffectManager, int ParticleCount,string Path)
	{
		FrameNumber = 0;
		EffElement = new EffectElement(this, Path);
		EffElement->ParticleArray = new Particle[ParticleCount];
		EffElement->ParticleCount = ParticleCount;
		this->EffectManager = EffectManager;
		this->ParticleArray = EffElement->ParticleArray;
		this->ParticleCount = ParticleCount;
		Inited = false;
		AddToManager();
	}
	~EffectBASE()
	{
		DeleteFromManager();
		delete EffElement;
	}

	void Refresh()
	{
		if (!Inited)
		{
			Init();
			Inited = true;
		}
		RefreshPosition();
	}
	
	

};

