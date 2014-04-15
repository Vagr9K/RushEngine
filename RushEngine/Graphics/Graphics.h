#pragma once

#include <vector>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_main.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "./SDL_test_common.h"
using namespace std;

#include "../Objects/Objects.h"

#include "DrawGL.h"


class GraphicsEngine
{


private:
	WindowInfo* WinData;
	string Title;
	bool IsReady;
	bool IsStarted;
	SDL_Window* mainWindow;
	EventingEngine* EventEngine;
	ObjectsEngine* ObjEngine;
	GraphicsManager* ManagerGR;
	SDLTest_CommonState* SystemState;
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
		WinData = new WindowInfo;
	}
	void RefreshData()
	{

	}

public:
	DrawGL* DrawerGL;
private:
	bool SystemInit()
	{
		SDLTest_CommonState* InitState;
		InitState = SDLTest_CommonCreateState(NULL, SDL_INIT_VIDEO);
		if (!InitState)
		{
			EventEngine->SystemEvents->GraphicsError("Cannot create initialization state.");
			return false;
		}
#ifdef __WINDOWS__
		InitState->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
#elif defined(__ANDROID__)
		InitState->window_flags |= SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_BORDERLESS;
		InitState->gl_profile_mask = SDL_GL_CONTEXT_PROFILE_ES;
#endif

		InitState->gl_major_version = 1;
		InitState->gl_minor_version = 1;
		InitState->gl_depth_size = 24;
		InitState->window_w = WinData->Width;
		InitState->window_h = WinData->Height;
		InitState->window_title = Title.c_str();

		if (!SDLTest_CommonInit(InitState))
		{
			EventEngine->SystemEvents->GraphicsError("Cannot init initialization state.");
			return false;
		}
		SystemState = InitState;
		mainWindow = InitState->windows[0];
		if (mainWindow == NULL)
		{
			EventEngine->SystemEvents->GraphicsError("NULL window pointer.");
			return false;
		}

		return true;

	}

	bool SystemDeInit()
	{
		SDLTest_CommonQuit(SystemState);
		return true;
	}
	
	void InitGL()
	{
		if (GLInited == false)
		{

			DrawerGL = new DrawGL(ManagerGR, mainWindow, EventEngine);
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
	GraphicsEngine(int Width, int Height, string Title, EventingEngine* EventsEnginePtr, ObjectsEngine* ObjEngine)
	{
		InitOldCpp();
		this->WinData->ZeroWidth = Width;
		this->WinData->ZeroHeight = Height;
		this->WinData->Width = Width;
		this->WinData->Height = Height;
		this->Title = Title;
		this->IsReady = true;
		this->EventEngine = EventsEnginePtr;
		this->ObjEngine = ObjEngine;
		EventEngine->GlobalVariables->WindowData = WinData;
	}
	void Init(int Width, int Height, string Title, EventingEngine* EvVar, ObjectsEngine* ObjEngine)
	{
		this->WinData->ZeroWidth = Width;
		this->WinData->ZeroHeight = Height;
		this->WinData->Width = Width;
		this->WinData->Height = Height;
		this->Title = Title;
		this->EventEngine = EvVar;
		this->ObjEngine = ObjEngine;
		this->IsReady = true;
		EventEngine->GlobalVariables->WindowData = WinData;
	}
	void SetWindowSize(int Width, int Height)
	{
		if (!IsStarted)
		{
			WinData->Width = Width;
			WinData->Height = Height;
		}
	}
	bool Start()
	{
		if (IsReady == false)
		{
			EventEngine->SystemEvents->GraphicsError("GraphicsEngine class is not initialized properly.");
			return false;
		}
		/*
#ifdef __ANDROID__
		mainWindow = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WinData->Width, WinData->Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
#else
		mainWindow = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WinData->Width, WinData->Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
#endif
		if (mainWindow == NULL)
		{
			EventEngine->SystemEvents->GraphicsError(SDL_GetError());
			return false;
		}
		*/
		
		if (!SystemInit())
		{
			EventEngine->SystemEvents->GraphicsError("Graphics system initialization failed.");
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

		this->ManagerGR = new GraphicsManager(EventEngine, ObjEngine, WinData);
		
		InitGL();

		IsStarted = true;
		return true;
	}

	void SetFullScreen(bool Fullscreen)
	{
		if (Fullscreen)
		{
			SDL_SetWindowFullscreen(mainWindow, SDL_WINDOW_FULLSCREEN);
		}
		else
		{
			SDL_SetWindowFullscreen(mainWindow, 0);
		}
	}
	~GraphicsEngine()
	{
		Stop();
		
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
		SystemDeInit();

		if (GLInited == true)
		{
			DeleteGL();
		}
		delete ManagerGR;

		IsStarted = false;
		return true;
	}
	void ShowMessageBox(string Title, string Message, MSGBOXMODE Type = INFORMATIONMessage)
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

	WindowInfo* getWindowData()
	{
		WindowInfo* Info;
		if (IsStarted)
		{
			return WinData;
		}
		Info = new WindowInfo();
		
		return Info;
	}


};


