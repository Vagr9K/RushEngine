#include "SDL.h"
#include "EventManagers.h"
struct Mouse
{

};

struct Keyboard
{
private:
	Input* MainClass;
	inline void RequestUpdate()
	{
		MainClass->Update();
	}
public:
	Keyboard(Input* InputPtr)
	{
		MainClass = InputPtr;
	}
	const Uint8* GetKeyStatusSC()
	{
		RequestUpdate();
		const Uint8* Keys = SDL_GetKeyboardState(NULL);
		return 	Keys;
	}

};
#ifdef __ANDROID__ // || #defined(__iOS__)
/*==============================================================================
 *	Android/iOS specific events will go here, after first tests on mobile. 
 *==============================================================================
 **/
//TODO: Mobile version of events.
#endif

class Input
{
	GlobalEventManager* MainClass;
public:
	void Update()
	{
		MainClass->Update();
	}
};