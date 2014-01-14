#include "SDL.h"
#include "EventManagers.h"






class MouseStatus
{
public:
	int X, Y, StartX, StartY, XRel, YRel;
	bool Motion;
	MouseButton ButtonDOWN;
	MouseButton ButtonUP;
	MouseStatus()
	{
		Motion = false;
	}
};

class MouseInput
{
	
private:
	GlobalEventManager* MainClass;
	SDL_Event* GlobalEvent;
	inline void RequestUpdate()
	{
		MainClass->Update();
	}

	void RefershStatus()
	{
		if (GlobalEvent->type == SDL_MOUSEMOTION)
		{
			Status.Motion = true;
			Status.XRel = GlobalEvent->motion.xrel;
			Status.YRel = GlobalEvent->motion.yrel;
			Status.X = GlobalEvent->motion.x;
			Status.Y = GlobalEvent->motion.y;
			Status.StartX = Status.X + Status.XRel;
			Status.StartY = Status.Y + Status.YRel;

		}
		else if (GlobalEvent->type == SDL_MOUSEBUTTONDOWN)
		{
			Status.Motion = false;
			SDL_GetMouseState(&Status.X, &Status.Y);
			if (GlobalEvent->button.button == SDL_BUTTON_LEFT)
			{
				Status.ButtonDOWN = LEFT;
			}
			if (GlobalEvent->button.button == SDL_BUTTON_RIGHT)
			{
				Status.ButtonDOWN = RIGHT;
			}

		}
		else if (GlobalEvent->type == SDL_MOUSEBUTTONUP)
		{
			Status.Motion = false;
			SDL_GetMouseState(&Status.X, &Status.Y);
			if (GlobalEvent->button.button == SDL_BUTTON_LEFT)
			{
				Status.ButtonUP = LEFT;
			}
			if (GlobalEvent->button.button == SDL_BUTTON_RIGHT)
			{
				Status.ButtonUP = RIGHT;
			}

		}
	}
	void SyncEvent()
	{
		GlobalEvent = &MainClass->GlobalEvent;
	}
public:
	MouseStatus Status;
	MouseInput(GlobalEventManager* MainManager)
	{
		this->MainClass = MainManager;
		SyncEvent();
	}
	void Refresh()
	{
		RequestUpdate();
		RefershStatus();
	}
};

class KeyboardInput
{
	
private:
	GlobalEventManager* MainClass;
	inline void RequestUpdate()
	{
		MainClass->Update();
	}
	
	inline void GetKeyStatusFK()
	{
		RequestUpdate();
		KeysStatus = SDL_GetKeyboardState(&KeyArrayLenght);

	}
public:
	const Uint8* KeysStatus;
	int KeyArrayLenght;
	KeyboardInput(GlobalEventManager* MainClass)
	{
		this->MainClass = MainClass;
		GetKeyStatusFK();
	}
	string GetKeyName(SDL_Keycode Key)
	{
		return string(SDL_GetKeyName(Key));
	}


};
#ifdef __ANDROID__ // || #defined(__iOS__)
/*==============================================================================
 *	Android/iOS specific events will go here, after first tests on mobile. 
 *==============================================================================
 **/
//TODO: Mobile version of events.
#endif

class InputController
{
	GlobalEventManager* MainClass;

public:
	MouseInput* Mouse;
	KeyboardInput* Keyboard;
	InputController(GlobalEventManager* MainClass)
	{
		this->MainClass = MainClass;
		Mouse = new MouseInput(MainClass);
		Keyboard = new KeyboardInput(MainClass);

	}
	void Update()
	{
		MainClass->Update();
	}
	friend class MouseInput;
	friend class KeyboardInput;
};