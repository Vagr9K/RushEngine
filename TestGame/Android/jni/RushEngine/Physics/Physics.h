#pragma once

#include "Box2D/Box2D.h"
#include <vector>
using namespace std;


class PhysicsEngine
{
private:
  vector <b2World*> PhysicsWorlds;
public:
  PhysicsEngine ();
  void AddWorld (b2World * NewWorld);
  vector <b2World*> * GetWorlds ();
};
