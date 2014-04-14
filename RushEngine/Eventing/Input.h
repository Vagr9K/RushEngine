#include "SDL.h"
#include "EventManagers.h"

#ifdef __WINDOWS__

class MouseStatus
{
public:
  int X;
  int Y;
  int StartX;
  int StartY;
  int XRel;
  int YRel;
  bool Motion;
  MouseButton ButtonDOWN;
  MouseButton ButtonUP;
  MouseStatus ();
};
class MouseInput
{
private:
  GlobalEventManager * MainClass;
  SDL_Event * GlobalEvent;
  void RequestUpdate ();
  void RefershStatus ();
  void SyncEvent ();
public:
  MouseStatus Status;
  MouseInput (GlobalEventManager * MainManager);
  void Refresh ();
};
class KeyboardInput
{
private:
  GlobalEventManager * MainClass;
  void RequestUpdate ();
  void GetKeyStatusFK ();
public:
  Uint8 const * KeysStatus;
  int KeyArrayLenght;
  KeyboardInput (GlobalEventManager * MainClass);
  ~KeyboardInput();
  string GetKeyName (SDL_Keycode Key);
};

#endif
class InputController
{
  GlobalEventManager * MainClass;
public:
  InputController (GlobalEventManager * MainClass);
  void Update ();
  ~InputController();
  #ifdef __WINDOWS__
  MouseInput * Mouse;
  KeyboardInput * Keyboard;
  friend class MouseInput;
  friend class KeyboardInput;

  #endif
};

