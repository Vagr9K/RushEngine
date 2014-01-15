#pragma once

#include <fstream>
#include <ios>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <string>
using namespace std;

#include "SDL.h"
#include "EventComponents.h"

#if __cplusplus <= 199711L
#define to_string(Number) to_string(static_cast<long long>(Number))
#endif


class SystemEventing : public Events
{
public:
  void LogData (string Type, string Data, bool Throw);
  void GraphicsError (string Error);
  void OPSLog (string OPS);
  void ObjectsError (string Error);
};
class GlobalEventManager
{
public:
  SDL_Event GlobalEvent;
public:
  void Update ();
};
