#pragma once

#include "EventManagers.h"
#include "Input.h"
using namespace std;


class EventingEngine : public GlobalEventManager
{
public:
  SystemEventing * SystemEvents;
  InputController * Input;
  EventingEngine ();
  ~EventingEngine();
};
