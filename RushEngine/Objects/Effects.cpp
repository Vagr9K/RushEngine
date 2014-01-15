#include "Effects.h"

void EffectBASE::AddToManager ()
        {
		EffectManager->AddToCreate(EffElement);
	}
void EffectBASE::DeleteFromManager ()
        {
		EffectManager->AddToCreate(EffElement);
	}
EffectBASE::EffectBASE (ObjDBManager <EffectElement> * EffectManager, int ParticleCount, string Path)
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
EffectBASE::~ EffectBASE ()
        {
		DeleteFromManager();
		delete EffElement;
	}
void EffectBASE::Refresh ()
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
void EffectBASE::Pause ()
        {
		Paused = true;
	}
void EffectBASE::Resume ()
        {
		Paused = false;
	}
void EffectBASE::Start ()
        {
		Ended = false;
	}
void EffectBASE::Stop ()
        {
		Ended = true;
		Init();
	}
void EffectBASE::ReStart ()
        {
		Init();
		Ended = false;
	}
