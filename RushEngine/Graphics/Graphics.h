#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

using namespace std;

#include "DrawGL.h"

//Platform dependent includes!
#ifdef __WINDOWS__
#include <SDL_opengl.h>
#elif __ANDROID__
//Android includes here!
#include <SDL_opengles.h>

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
	GraphicsEngine(int Width, int Height, int LayerNumber, string Title, EventingEngine* EventsEnginePtr)
	{
		InitOldCpp();
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->IsReady = true;
		this->EventEngine = EventsEnginePtr;
		
	}
	void Init(int Width, int Height, int LayerNumber, string Title, EventingEngine* EvVar)
	{
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->EventEngine = EvVar;
		this->IsReady = true;
		
	}

	bool Start()
	{
		if (IsReady == false)
		{
			EventEngine->SystemEvents.GraphicsError("GraphicsEngine class is not initialized properly.");
			return false;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			EventEngine->SystemEvents.GraphicsError(SDL_GetError());
			return false;
		}
		mainWindow = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (mainWindow == NULL)
		{
			EventEngine->SystemEvents.GraphicsError(SDL_GetError());
			return false;
		}
		if (TTF_Init() < 0)
		{
			EventEngine->SystemEvents.GraphicsError(TTF_GetError());
		}

		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat != IMGFlags)
		{
			EventEngine->SystemEvents.GraphicsError(IMG_GetError());
			return false;
		}
		
		this->ManagerGR = new GraphicsManager(EventEngine);

		InitGL();

		IsStarted = true;
		return true;
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
	void Delay(int Milliseconds)
	{
		SDL_Delay(Milliseconds);
	}

	WindowInfo getWindowSize()
	{
		WindowInfo Info;
		SDL_GetWindowSize(mainWindow, &Info.Width, &Info.Height);
		return Info;
	}

	
};


