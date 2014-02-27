#include "ObjectManager.h"

class EffectBASE
{
private:
  bool Inited;
  bool Paused;
  bool Ended;
  ObjDBManager <EffectElement> * EffectManager;
protected:
  int ParticleCount;
  Particle * ParticleArray;
  EffectElement * EffElement;
private:
  void AddToManager ();
  void DeleteFromManager ();
protected:
  virtual void Init () = 0;
  virtual void RefreshPosition () = 0;

  void SetBlendMode(EffectDrawMode Mode);
public:
  EffectBASE (ObjDBManager <EffectElement> * EffectManager, int ParticleCount, string Path);
  ~ EffectBASE ();
  void Refresh ();
  void Pause ();
  void Resume ();
  void Start ();
  void Stop ();
  void ReStart ();
};
