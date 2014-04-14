#include "Input.h"

#ifdef __WINDOWS__

MouseStatus::MouseStatus ()
        {
		Motion = false;
	}
void MouseInput::RefershStatus ()
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
void MouseInput::SyncEvent ()
        {
		GlobalEvent = &MainClass->GlobalEvent;
	}
MouseInput::MouseInput (GlobalEventManager * MainManager)
        {
		this->MainClass = MainManager;
		SyncEvent();
	}
void MouseInput::Refresh ()
        {
		RequestUpdate();
		RefershStatus();
	}
KeyboardInput::KeyboardInput (GlobalEventManager * MainClass)
        {
		this->MainClass = MainClass;
		GetKeyStatusFK();
	}
string KeyboardInput::GetKeyName (SDL_Keycode Key)
        {
		return string(SDL_GetKeyName(Key));
	}

KeyboardInput::~KeyboardInput()
{
	
}

void MouseInput::RequestUpdate()
{
	MainClass->Update();
}
void KeyboardInput::RequestUpdate()
{
	MainClass->Update();
}
void KeyboardInput::GetKeyStatusFK()
{
	RequestUpdate();
	KeysStatus = SDL_GetKeyboardState(&KeyArrayLenght);

}
#endif

InputController::InputController(GlobalEventManager * MainClass)
        {
		this->MainClass = MainClass;
		#ifdef __WINDOWS__
		Mouse = new MouseInput(MainClass);
		Keyboard = new KeyboardInput(MainClass);
		#endif

	}
void InputController::Update ()
        {
		MainClass->Update();
	}

InputController::~InputController()
{
	#ifdef __WINDOWS__
	delete Mouse;
	delete Keyboard;
	#endif
}


