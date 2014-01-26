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


};

