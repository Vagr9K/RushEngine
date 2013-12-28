#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
using namespace std;



#include "DrawCPU.h"
#include "DrawGPU.h"
#include "DrawGL.h"
//Platform dependent includes!
#ifdef __WINDOWS__

#elif __ANDROID__
//Android includes here!

#endif 


class GraphicsEngine
{
	

private:
	int Width, Height, LayerNumber;
	string Title;
	bool IsReady;
	bool IsStarted;
	SDL_Window* mainWindow;
	SDL_Renderer *Renderer;
	EventingEngine* EventEngine;
	GraphicsManager* ManagerGR;

	
	bool CPUInited;
	bool GLInited;
	bool GPUInited;
	vector<SDL_Surface*> PreLoadedSurfCPU;
	vector<SDL_Texture*> PreLoadedTextGPU;
	vector<string> PreLoadedPathsCPU;
	vector<string> PreLoadedPathsGPU;
private:
	void InitOldCpp()
	{
		Title = "Default";
		IsReady = false;
		IsStarted = false;
		mainWindow = NULL;
		Renderer = NULL;
		EventEngine = NULL;
		ManagerGR = NULL;
		CPUInited = false;
		GPUInited = false;
		GLInited = false;
	}
	

public:
	DrawCPU* DrawerCPU;
	DrawGPU* DrawerGPU;
	DrawGL* DrawerGL;


public:
	GraphicsEngine()
	{
		InitOldCpp();
	}
	GraphicsEngine(int Width, int Height, int LayerNumber, string Title, EventingEngine* Events)
	{
		InitOldCpp();
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->IsReady = true;
		this->EventEngine = Events;
		
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


		Renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
		if (Renderer == NULL)
		{
			EventEngine->SystemEvents.GraphicsError(SDL_GetError());

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
		



		
		this->ManagerGR = new GraphicsManager(EventEngine, Renderer);
		IsStarted = true;
		return true;
	}
	
	void InitCPU()
	{
		DrawerCPU = new DrawCPU(ManagerGR, mainWindow);
		CPUInited = true;
		
	}

	void DeleteCPU()
	{
		DrawerCPU->~DrawCPU();
		CPUInited = false;
	}

	void InitGPU()
	{
		DrawerGPU = new DrawGPU(ManagerGR, Renderer, mainWindow, EventEngine);
		
		GPUInited = true;
	}

	void DeleteGPU()
	{
		DrawerGPU->~DrawGPU();
		GPUInited = false;
	}
	void InitGL()
	{
		DrawerGL = new DrawGL(ManagerGR, mainWindow, Height, Width, EventEngine);
		GLInited = true;
	}
	void DeleteGL()
	{
		DrawerGL->~DrawGL();
		GLInited = false;
	}

	bool Stop()
	{
		
		SDL_DestroyWindow(mainWindow);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		if (CPUInited == true)
		{
			DeleteCPU();
		}
		if (GPUInited == true)
		{
			DeleteGPU();
		}
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


