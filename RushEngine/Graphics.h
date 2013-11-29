#include <iostream>
#include <vector>
#include <assert.h>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "Eventing.h"


using namespace std;
enum Mode
{
	SOLID,
	SHADED,
	BLENDED,

};
enum Style

{
	NORMAL,
	BOLD,
	ITALIC,
	STRIKETHROUGH,
	UNDERLINE

};
class GameEngine;

struct TextFont
{


	string FontPath;
	int PointSize=12;
	int FontOutline =0;
	Style FontStyle = NORMAL;
	int Index = 0;
	bool FontKerning = false;


public:

	TextFont(string FontPath)
	{
		this->FontPath = FontPath;

	}
};


class GraphicsManager
{

	vector<SDL_Surface*>* PreLoadedSurfCPU=NULL;
	vector<SDL_Texture*>* PreLoadedTextGPU=NULL;
	vector<string>* PreLoadedPathsCPU=NULL;
	vector<string>* PreLoadedPathsGPU=NULL;
	EventingEngine* EventEngine=NULL;
	SDL_Renderer* Renderer=NULL;
	int OptimalObjectCount=0;

	vector<TTF_Font*> LoadedFonts;
	vector<string> LoadedFontsPaths;
	vector<SDL_Surface*> LoadedTextsCPU;
	vector<string> LoadedTextArgsCPU;
	vector<string> LoadedTextArgsGPU;
	vector<SDL_Texture*> LoadedTextsGPU;
	vector<int> TimeFromLastUseCPU;
	vector<int> TimeFromLastUseGPU;
	int MaximumTimeFromLastUse = 40;


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
	GraphicsManager(EventingEngine *EventEngine, SDL_Renderer* Renderer, int OptimalObjectCount)
	{
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		this->OptimalObjectCount = OptimalObjectCount;
		InitPreloaders();
	}

	void SetOptimalObjectCount(int OptimalObjectCount)
	{
		this->OptimalObjectCount = OptimalObjectCount;
	}

	int GetOptimalObjectCount()
	{
		return this->OptimalObjectCount;
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
		this->PreLoadedPathsCPU = new vector<string>(OptimalObjectCount);
		this->PreLoadedPathsGPU = new vector<string>(OptimalObjectCount);
		this->PreLoadedSurfCPU = new vector <SDL_Surface*>(OptimalObjectCount);
		this->PreLoadedTextGPU = new vector<SDL_Texture*>(OptimalObjectCount);
	}
	
	TTF_Font* LoadFont(string FontPath, int PointSize, int Index = 0)
	{
		TTF_Font* Font = NULL;
		if (Index == 0)
		{
			Font = TTF_OpenFont(FontPath.c_str(), PointSize);
			if (Font == NULL)
			{
				EventEngine->GraphicsError(TTF_GetError());

			}
			return Font;
		}
		else
		{
			Font = TTF_OpenFontIndex(FontPath.c_str(), PointSize, Index);
			if (Font == NULL)
			{
				EventEngine->GraphicsError(TTF_GetError());

			}
			return Font;
		}
		return Font;

	}

	TTF_Font* GetFont(string FontPath, int PointSize, int FontOutline, Style FontStyle, int Index = 0, bool FontKerning = false)
	{
		string Path = FontPath + to_string(PointSize) + to_string(Index);
		for (unsigned int i = 0; i < LoadedFontsPaths.size(); i++)
		{
			if (LoadedFontsPaths.at(i) == Path)
			{
				return LoadedFonts.at(i);
			}
		}




		TTF_Font* Font = LoadFont(FontPath, PointSize, Index);
		if (FontOutline != 0)
		{
			TTF_SetFontOutline(Font, FontOutline);

		}
		if (FontKerning == true)
		{
			TTF_SetFontKerning(Font, 1);
		}
		switch (FontStyle)
		{
		case NORMAL:
			TTF_SetFontStyle(Font, TTF_STYLE_NORMAL);
			break;
		case BOLD:
			TTF_SetFontStyle(Font, TTF_STYLE_BOLD);
			break;
		case ITALIC:
			TTF_SetFontStyle(Font, TTF_STYLE_ITALIC);
			break;
		case STRIKETHROUGH:
			TTF_SetFontStyle(Font, TTF_STYLE_STRIKETHROUGH);
			break;
		case UNDERLINE:
			TTF_SetFontStyle(Font, TTF_STYLE_UNDERLINE);
			break;
		default:
			break;
		}
		LoadedFonts.push_back(Font);
		LoadedFontsPaths.push_back(Path);
		return Font;

	}



	SDL_Surface* GetTextImageCPU(TextFont* Font,string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background)
	{
		SDL_Surface* Surf = NULL;
		string args = to_string(Font->FontKerning) + to_string(Font->FontOutline)
			+ Font->FontPath + to_string(Font->FontStyle) + to_string(Font->Index)
			+ to_string(Font->PointSize) + Text;
		for (unsigned int i = 0; i < TimeFromLastUseCPU.size(); i++)
		{
			if (LoadedTextArgsCPU.at(i) == args)
			{
				
				TimeFromLastUseCPU.at(i) = 0;
				return LoadedTextsCPU.at(i);
				Surf = LoadedTextsCPU.at(i);
				break;
			}
			else
			{
				if (TimeFromLastUseCPU.at(i)>=MaximumTimeFromLastUse)
				{
					LoadedTextsCPU.erase(LoadedTextsCPU.begin() + i);
					TimeFromLastUseCPU.erase(TimeFromLastUseCPU.begin() + i);
					LoadedTextArgsCPU.erase(LoadedTextArgsCPU.begin() + i);
					i--;

				} 
				else
				{
					TimeFromLastUseCPU.at(i)++;
				}
			}
		}
		TTF_Font* TTFFONT = GetFont(Font->FontPath, Font->PointSize, Font->FontOutline, Font->FontStyle, Font->Index, Font->FontKerning);
		switch (DrawMode)
		{
		case SOLID:
			Surf = GetSurfaceSolid(TTFFONT, Text, Foregroung);
			break;
		case SHADED:
			Surf = GetSurfaceShaded(TTFFONT, Text, Foregroung, Background);
			break;
		case BLENDED:
			Surf = GetSurfaceBlended(TTFFONT, Text, Foregroung);
			break;
		default:
			break;
		}
		LoadedTextsCPU.push_back(Surf);
		TimeFromLastUseCPU.push_back(0);
		LoadedTextArgsCPU.push_back(args);



		return Surf;
	}


	SDL_Texture* GetTextImageGPU(TextFont* Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background)
	{
		SDL_Texture* Texture = NULL;
		string args = to_string(Font->FontKerning) + to_string(Font->FontOutline)
			+ Font->FontPath + to_string(Font->FontStyle) + to_string(Font->Index)
			+ to_string(Font->PointSize) + Text;
		for (unsigned int i = 0; i < TimeFromLastUseGPU.size(); i++)
		{
			if (LoadedTextArgsGPU.at(i) == args)
			{

				TimeFromLastUseGPU.at(i) = 0;
				return LoadedTextsGPU.at(i);
				Texture = LoadedTextsGPU.at(i);
				break;
			}
			else
			{
				if (TimeFromLastUseGPU.at(i) >= MaximumTimeFromLastUse)
				{
					LoadedTextsGPU.erase(LoadedTextsGPU.begin() + i);
					TimeFromLastUseGPU.erase(TimeFromLastUseGPU.begin() + i);
					LoadedTextArgsGPU.erase(LoadedTextArgsGPU.begin() + i);
					i--;

				}
				else
				{
					TimeFromLastUseGPU.at(i)++;
				}
			}
		}
		TTF_Font* TTFFONT = GetFont(Font->FontPath, Font->PointSize, Font->FontOutline, Font->FontStyle, Font->Index, Font->FontKerning);
		switch (DrawMode)
		{
		case SOLID:
			Texture = SDL_CreateTextureFromSurface(Renderer,GetSurfaceSolid(TTFFONT, Text, Foregroung));
			break;
		case SHADED:
			Texture = SDL_CreateTextureFromSurface(Renderer,GetSurfaceShaded(TTFFONT, Text, Foregroung, Background));
			break;
		case BLENDED:
			Texture = SDL_CreateTextureFromSurface(Renderer, GetSurfaceBlended(TTFFONT, Text, Foregroung));
			break;
		default:
			break;
		}
		LoadedTextsGPU.push_back(Texture);
		TimeFromLastUseGPU.push_back(0);
		LoadedTextArgsGPU.push_back(args);



		return Texture;
	}



	SDL_Surface* GetSurfaceSolid(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Solid(Font, Text.c_str(), Foreground);
		if (Surf == NULL)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}
		return Surf;
	}

	SDL_Surface* GetSurfaceShaded(TTF_Font* Font, string Text, SDL_Color Foreground, SDL_Color Background)
	{
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Shaded(Font, Text.c_str(), Foreground, Background);
		if (Surf == NULL)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}
		return Surf;
	}

	SDL_Surface* GetSurfaceBlended(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Blended(Font, Text.c_str(), Foreground);
		if (Surf == NULL)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}
		return Surf;
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
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground)
	{
		SDL_Color Background;
		Background.a = 0;
		Background.b = 0;
		Background.g = 0;
		Background.r = 0;
		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->GetTextImageCPU(Font, Text, DrawMode, Foreground, Background), NULL, WinSurf, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->GetTextImageCPU(Font, Text, DrawMode, Foreground, Background), NULL, WinSurf, &CopyTo);

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
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->GetTextImageGPU(Font, Text, DrawMode, Foreground, Background), NULL, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground)
	{
		SDL_Color Background;
		Background.a = 0;
		Background.b = 0;
		Background.g = 0;
		Background.r = 0;
		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->GetTextImageGPU(Font, Text, DrawMode, Foreground, Background), NULL, &CopyTo);

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
		if (TTF_Init() < 0)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}

		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat != IMGFlags)
		{
			EventEngine->GraphicsError(IMG_GetError());
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

	
	bool Stop()
	{
		
		SDL_DestroyWindow(mainWindow);
		IMG_Quit();
		TTF_Quit();
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


