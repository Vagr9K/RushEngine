#include "ObjectManager.h"

class EffectBASE
{
protected:
	EffectElement* EffElement;
	ObjDBManager<EffectElement>* EffectManager;
protected:
	int FrameNumber;
	Particle* ParticleArray;
	void AddToManager()
	{
		EffectManager->AddToCreate(EffElement);
	}
	void DeleteFromManager()
	{
		EffectManager->AddToCreate(EffElement);
	}
public:
	EffectBASE(ObjDBManager<EffectElement>* EffectManager, string Path)
	{
		FrameNumber = 0;
		EffElement = new EffectElement(this, Path);
		this->EffectManager = EffectManager;
		this->ParticleArray = EffElement->ParticleArray;
		Init();
		AddToManager();
	}
	~EffectBASE()
	{
		DeleteFromManager();
		delete EffElement;
	}
	virtual void Init() = 0;

	virtual void RefreshPosition() = 0;

};


