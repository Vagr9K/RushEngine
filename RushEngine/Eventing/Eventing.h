#pragma once

#include "EventManagers.h"
#include "Input.h"
#include "GlobalVars.h"
using namespace std;


class EventingEngine : public GlobalEventManager
{
public:
  SystemEventing * SystemEvents;
  InputController * Input;
  GlobalVars* GlobalVariables;
  EventingEngine ();
  ~EventingEngine();
};
