#include "../GameEngineRAW.h"

class Effect : public EffectBASE
{
public:
	Effect(ObjDBManager <EffectElement> * EffectManager, int ParticleCount, string Path)
		:EffectBASE(EffectManager, ParticleCount, Path)
	{

	}
	Effect(int ParticleCount, string Path)
		:EffectBASE(RushEngineInfo.EffectDatabase, ParticleCount, Path)
	{

	}
	Effect(int LayerID, int ParticleCount, string Path)
		:EffectBASE(RushEngineInfo.Objects->getEffectManager(LayerID), ParticleCount, Path)
	{

	}

};

