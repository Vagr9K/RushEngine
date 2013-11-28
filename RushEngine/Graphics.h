#include <iostream>
#include <vector>
#include <assert.h>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "Eventing.h"


using namespace std;

class GraphicsManager
{

	vector<SDL_Surface*>* PreLoadedSurfCPU=NULL;
	vector<SDL_Texture*>* PreLoadedTextGPU=NULL;
	vector<string>* PreLoadedPathsCPU=NULL;
	vector<string>* PreLoadedPathsGPU=NULL;
	EventingEngine* EventEngine=NULL;
	SDL_Renderer* Renderer=NULL;


public:
	GraphicsManager(EventingEngine *EventEngine, SDL_Renderer* Renderer, 
		vector<SDL_Surface*>* PreLoadedSurfCPU, vector<SDL_Texture*>* PreLoadedTextGPU, 
		vector<string>* PreLoadedPathsCPU, vector<string>* PreLoadedPathsGPU)
	{
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		this->PreLoadedPathsCPU = PreLoadedPathsCPU;
		this->PreLoadedPathsGPU = PreLoadedPathsGPU;
		this->PreLoadedSurfCPU = PreLoadedSurfCPU;
		this->PreLoadedTextGPU = PreLoadedTextGPU;
	}
	GraphicsManager(EventingEngine *EventEngine, SDL_Renderer* Renderer)
	{
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		InitPreloaders();
	}

	void InitPreloaders()
	{
		if (PreLoadedPathsCPU !=NULL)
		{
			delete[] PreLoadedPathsCPU;
		}
		if (PreLoadedPathsGPU != NULL)
		{
			delete[] PreLoadedPathsGPU;
		}
		if (PreLoadedSurfCPU != NULL)
		{
			delete[] PreLoadedSurfCPU;
		}
		if (PreLoadedTextGPU != NULL)
		{
			delete[] PreLoadedTextGPU;
		}
		this->PreLoadedPathsCPU = new vector<string>;
		this->PreLoadedPathsGPU = new vector<string>;
		this->PreLoadedSurfCPU = new vector <SDL_Surface*>;
		this->PreLoadedTextGPU = new vector<SDL_Texture*>;
	}
	
	SDL_Surface* LoaderCPU(string Path)
	{
		SDL_Surface* Temp = NULL;
		bool SurfPresent = false;
		for (unsigned int i = 0; i < PreLoadedPathsCPU->size(); i++)
		{
			if (PreLoadedPathsCPU->at(i) == Path)
			{
				Temp = PreLoadedSurfCPU->at(i);
				SurfPresent = true;
				break;
			}
		}
		if (SurfPresent == false)

		{
			PreLoadedSurfCPU->push_back(IMGLoad(Path));
			PreLoadedPathsCPU->push_back(Path);
			Temp = PreLoadedSurfCPU->back();
		}
		return Temp;
	}
	
	bool PreLoadCPU(string Path, bool CheckExistance = true)
	{
		if (CheckExistance == true)
		{
			for (unsigned int i = 0; i < PreLoadedPathsCPU->size(); i++)
			{
				if (PreLoadedPathsCPU->at(i) == Path)
				{
					return true;
				}
			}
		}
		PreLoadedSurfCPU->push_back(IMGLoad(Path));
		return true;
	}
	void ClearPreLoadCPU(double PartToClear)
	{
		unsigned int Size = PreLoadedPathsCPU->size();
		int Count =static_cast<int>(Size*PartToClear);


		PreLoadedSurfCPU->erase(PreLoadedSurfCPU->begin(), PreLoadedSurfCPU->begin() + Count);
		PreLoadedPathsCPU->erase(PreLoadedPathsCPU->begin(), PreLoadedPathsCPU->begin() + Count);
	}

	



	SDL_Surface* IMGLoad(string Path)
	{
		SDL_Surface* Surface = IMG_Load(Path.c_str());
		if (Surface == NULL)
		{
			EventEngine->GraphicsError(IMG_GetError());
		}


		return Surface;
	}
	SDL_Texture* LoaderGPU(string Path)
	{
		SDL_Texture* Temp = NULL;
		bool TextPresent = false;
		for (unsigned int i = 0; i < PreLoadedPathsGPU->size(); i++)
		{
			if (PreLoadedPathsGPU->at(i) == Path)
			{
				Temp = PreLoadedTextGPU->at(i);
				TextPresent = true;
				break;
			}
		}
		if (TextPresent == false)
	
		{
			PreLoadedTextGPU->push_back(SDL_CreateTextureFromSurface(Renderer, IMGLoad(Path)));
			PreLoadedPathsGPU->push_back(Path);
			Temp = PreLoadedTextGPU->back();
		}
		return Temp;
	}
	void PreLoadGPU(string Path, bool CheckExistance = true)
	{
		bool Exists = false;
		if (CheckExistance == true)
		{
			for (unsigned int i = 0; i < PreLoadedPathsGPU->size(); i++)
			{
				if (PreLoadedPathsGPU->at(i) == Path)
				{
					Exists = true;
					break;
				}
			}
		}
		if (Exists == false)
		{
			PreLoadedTextGPU->push_back(SDL_CreateTextureFromSurface(Renderer, IMGLoad(Path)));
		}
		
	}
	void ClearPreLoadGPU(double PartToClear)
	{
		unsigned int Size = PreLoadedPathsGPU->size();
		int Count = static_cast<int>(Size*PartToClear);


		PreLoadedTextGPU->erase(PreLoadedTextGPU->begin(), PreLoadedTextGPU->begin() + Count);
		PreLoadedPathsGPU->erase(PreLoadedPathsGPU->begin(), PreLoadedPathsGPU->begin() + Count);
	}
	
	
};



class DrawCPU
{


	SDL_Window* Window = NULL;
	SDL_Surface* WinSurf = NULL;
	SDL_Rect CopyFrom;
	SDL_Rect CopyTo;
	GraphicsManager* ManagerGR = NULL;

public:
	DrawCPU(GraphicsManager* ManagerGR, SDL_Window* mainWindow)
	{
		this->Window = mainWindow;
		this->ManagerGR = ManagerGR;
		WinSurf = SDL_GetWindowSurface(Window);

	}
	~DrawCPU()
	{
		ClearAll();

	}


	void StartBuffer()
	{
		SDL_FillRect(WinSurf, NULL, SDL_MapRGB(WinSurf->format, 0, 0, 0));
	}


	void AddToBuffer(int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source)
	{
		CopyFrom.h = OrigH;
		CopyFrom.w = OrigW;
		CopyFrom.x = OrigX;
		CopyFrom.y = OrigY;
		CopyTo.h = CopyH;
		CopyTo.w = CopyW;
		CopyTo.x = CopyX;
		CopyTo.y = CopyY;
		SDL_BlitSurface(ManagerGR->LoaderCPU(Source), &CopyFrom, WinSurf, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Source)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->LoaderCPU(Source), NULL, WinSurf, &CopyTo);

	}

	void PushBuffer()
	{
		SDL_UpdateWindowSurface(Window);
	}

	void ClearAll()
	{
		ManagerGR->ClearPreLoadCPU(1.0);
		SDL_FreeSurface(WinSurf);
	}

};

class DrawGPU
{


	SDL_Rect CopyFrom;
	SDL_Rect CopyTo;
	SDL_Renderer *Render = NULL;
	SDL_Window* mainWindow;
	GraphicsManager* ManagerGR = NULL;



public:
	DrawGPU(GraphicsManager* ManagerGR, SDL_Renderer* Render, SDL_Window* mainWindow, EventingEngine* Events)
	{

		this->ManagerGR = ManagerGR;
		this->mainWindow = mainWindow;
		this->Render = Render;
		if (Render == NULL)
		{
			Events->GraphicsError("Renderer not initialized for DrawGPU.");
		}
	}

	~DrawGPU()
	{
		ClearAll();

	}

	void StartBuffer()
	{
		SDL_RenderClear(Render);
	}


	void AddToBuffer(int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source)
	{
		CopyFrom.h = OrigH;
		CopyFrom.w = OrigW;
		CopyFrom.x = OrigX;
		CopyFrom.y = OrigY;
		CopyTo.h = CopyH;
		CopyTo.w = CopyW;
		CopyTo.x = CopyX;
		CopyTo.y = CopyY;
		SDL_RenderCopy(Render, ManagerGR->LoaderGPU(Source), &CopyFrom, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Source)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->LoaderGPU(Source), NULL, &CopyTo);

	}
	void PushBuffer()
	{
		SDL_RenderPresent(Render);
	}



	void ClearAll()
	{
		ManagerGR->ClearPreLoadGPU(1.0);

	}
};

struct WindowInfo
{
	int Height;
	int Width;
};


class GraphicsEngine
{
	

private:
	int Width, Height, LayerNumber;
	string Title = "Default";
	bool IsReady = false;
	bool IsStarted = false;
	SDL_Window* mainWindow = NULL;
	SDL_Renderer *Renderer = NULL;
	EventingEngine* EventEngine = NULL;
	GraphicsManager* ManagerGR = NULL;
	
	bool CPUInited = false;

	bool GPUInited = false;
	vector<SDL_Surface*> PreLoadedSurfCPU;
	vector<SDL_Texture*> PreLoadedTextGPU;
	vector<string> PreLoadedPathsCPU;
	vector<string> PreLoadedPathsGPU;
	

public:
	DrawCPU* DrawerCPU;
	DrawGPU* DrawerGPU;



public:
	GraphicsEngine(){}
	GraphicsEngine(int Width, int Height, int LayerNumber, string Title, EventingEngine* Events)
	{
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
			EventEngine->GraphicsError("GraphicsEngine class is not initialized properly.");
			return false;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			EventEngine->GraphicsError(SDL_GetError());
			return false;
		}
		mainWindow = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
		if (mainWindow == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());
			return false;
		}


		Renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
		if (Renderer == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());

		}
		
		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat != IMGFlags)
		{
			EventEngine->GraphicsError(IMG_GetError());
			return false;
		}



		//this->ManagerGR = new GraphicsManager(EventEngine, Render, &PreLoadedSurfCPU, &PreLoadedTextGPU,&PreLoadedPathsCPU, &PreLoadedPathsGPU);
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

	
	bool Stop()
	{
		
		SDL_DestroyWindow(mainWindow);
		IMG_Quit();
		SDL_Quit();

		if (CPUInited==true)
		{
			DeleteCPU();
		}
		if (GPUInited==true)
		{
			DeleteGPU();
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


