#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

using namespace std;

#include "../Objects/Objects.h"

#include "DrawGL.h"

//Platform dependent includes!
#ifdef __WINDOWS__
#include <SDL_opengl.h>
#elif __ANDROID__
#include <SDL_opengles.h>
typedef glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) glOrthof(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar)
#endif 


class GraphicsEngine
{
	

private:
	int Width, Height, LayerNumber;
	string Title;
	bool IsReady;
	bool IsStarted;
	SDL_Window* mainWindow;
	EventingEngine* EventEngine;
	ObjectsEngine* ObjEngine;
	GraphicsManager* ManagerGR;

	bool GLInited;
private:
	void InitOldCpp()
	{
		Title = "Default";
		IsReady = false;
		IsStarted = false;
		mainWindow = NULL;
		EventEngine = NULL;
		ObjEngine = NULL;
		ManagerGR = NULL;
		GLInited = false;
	}
	

public:
	DrawGL* DrawerGL;
private:
	void InitGL()
	{
		if (GLInited==false)
		{

			DrawerGL = new DrawGL(ManagerGR, mainWindow, Height, Width, EventEngine);
			GLInited = true;
		}
	}
	void DeleteGL()
	{
		if (GLInited == true)
		{

			DrawerGL->~DrawGL();
			GLInited = false;
		}
	}

public:
	GraphicsEngine()
	{
		InitOldCpp();
	}
	GraphicsEngine(int Width, int Height, int LayerNumber, string Title, EventingEngine* EventsEnginePtr, ObjectsEngine* ObjEngine)
	{
		InitOldCpp();
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->IsReady = true;
		this->EventEngine = EventsEnginePtr;
		this->ObjEngine = ObjEngine;
	}
	void Init(int Width, int Height, int LayerNumber, string Title, EventingEngine* EvVar, ObjectsEngine* ObjEngine)
	{
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->EventEngine = EvVar;
		this->ObjEngine = ObjEngine;
		this->IsReady = true;
		
	}

	bool Start()
	{
		if (IsReady == false)
		{
			EventEngine->SystemEvents->GraphicsError("GraphicsEngine class is not initialized properly.");
			return false;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			EventEngine->SystemEvents->GraphicsError(SDL_GetError());
			return false;
		}
		mainWindow = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (mainWindow == NULL)
		{
			EventEngine->SystemEvents->GraphicsError(SDL_GetError());
			return false;
		}
		if (TTF_Init() < 0)
		{
			EventEngine->SystemEvents->GraphicsError(TTF_GetError());
		}

		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat != IMGFlags)
		{
			EventEngine->SystemEvents->GraphicsError(IMG_GetError());
			return false;
		}
		
		this->ManagerGR = new GraphicsManager(EventEngine, ObjEngine);

		InitGL();

		IsStarted = true;
		return true;
	}
	void SetTextMaximumTime(int Time)
	{
		ManagerGR->SetMaximumTimeOfText(Time);
	}

	bool Stop()
	{
		
		SDL_DestroyWindow(mainWindow);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		if (GLInited==true)
		{
			DeleteGL();
		}

		
		IsStarted = false;
		return true;
	}
	void ShowMessageBox(string Title, string Message, MSGBOXMODE Type)
	{
		switch (Type)
		{
		case ERRORMessage:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, Title.c_str(), Message.c_str(), NULL);
			break;
		case WARNINGMessage:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, Title.c_str(), Message.c_str(), NULL);
			break;
		case INFORMATIONMessage:
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, Title.c_str(), Message.c_str(), NULL);
			break;
		default:
			break;
		}
		
	}

	void TrapMouse(bool Status)
	{
		if (Status)
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
		else
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
	}

	WindowInfo getWindowSize()
	{
		WindowInfo Info;
		SDL_GetWindowSize(mainWindow, &Info.Width, &Info.Height);
		return Info;
	}

	
};


