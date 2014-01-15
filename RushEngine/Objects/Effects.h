#include "ObjectManager.h"

class EffectBASE
{

private:
	bool Inited;
	bool Paused;
	bool Ended;
	ObjDBManager<EffectElement>* EffectManager;
protected:
	int ParticleCount;
	Particle* ParticleArray;
	EffectElement* EffElement;
private:
	void AddToManager()
	{
		EffectManager->AddToCreate(EffElement);
	}

	void DeleteFromManager()
	{
		EffectManager->AddToCreate(EffElement);
	}
protected:
	virtual void Init() = 0;

	virtual void RefreshPosition() = 0;


public:
	EffectBASE(ObjDBManager<EffectElement>* EffectManager, int ParticleCount,string Path)
	{
		EffElement = new EffectElement(this, Path);
		EffElement->ParticleArray = new Particle[ParticleCount];
		EffElement->ParticleCount = ParticleCount;
		this->EffectManager = EffectManager;
		this->ParticleArray = EffElement->ParticleArray;
		this->ParticleCount = ParticleCount;
		Paused = false;
		Inited = false;
		Ended = false;
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
		if (Paused == false || Ended == true)
		{
			RefreshPosition();
		}
	}
	void Pause()
	{
		Paused = true;
	}
	void Resume()
	{
		Paused = false;
	}
	void Start()
	{
		Ended = false;
	}

	void Stop()
	{
		Ended = true;
		Init();
	}
	void ReStart()
	{
		Init();
		Ended = false;
	}

};

