

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "Eventing.h"


#include <iostream>
#include <vector>


using namespace std;

class Graphics
{
private:
	int Width, Height, LayerNumber;
	char Title;
	bool IsReady = false; 
	SDL_Window* main = NULL;
	SDL_Renderer *Render = NULL;
	vector<SDL_Surface*> PreLoadedSurf;
	vector<string> PreLoadedPaths;
	GEEventing* EvSys;
	SDL_Surface* TEMP;
public:
	Graphics(){}
	Graphics(int Width, int Height, int LayerNumber,string Title, GEEventing* EvVar)
	{
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = *(Title.c_str());
		this->IsReady = true;
		this->EvSys = EvVar;
	}
	void Init(int Width, int Height, int LayerNumber, string Title, GEEventing* EvVar)
	{
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = *(Title.c_str());
		this->EvSys = EvVar;
		this->IsReady = true;
	}
	
	bool Start()
	{
		if (IsReady==false)
		{
			return false;
		} 
	
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			EvSys->OnGraphicsError(SDL_GetError());
			return false;
		}
		main = SDL_CreateWindow(&Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
		if (main==NULL)
		{
			EvSys->OnGraphicsError(SDL_GetError());
			return false;
		}
		Render = SDL_CreateRenderer(main, -1, SDL_RENDERER_ACCELERATED);
		if (Render==NULL)
		{
			EvSys->OnGraphicsError(SDL_GetError());
			return false;
		}

		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat != IMGFlags)
		{
			EvSys->OnGraphicsError(IMG_GetError());
			return false;
		}



		return true;
	}

	bool Stop()
	{
		SDL_DestroyRenderer(Render);
		SDL_DestroyWindow(main);
		IMG_Quit();
		SDL_Quit();
		return true;
	}
	void DelayGraphics(int Milliseconds)
	{
		SDL_Delay(Milliseconds);
	}

	void BlackInit()
	{
		
		SDL_Rect rectData;
		rectData.h = Height;
		rectData.w = Width;
		rectData.x = 0;
		rectData.y = 0;
		SDL_Surface* TEMP = Loader("images/BlackInit.png");
		SDL_Texture* Texture = SDL_CreateTextureFromSurface(Render, TEMP);
		SDL_RenderClear(Render);
		SDL_RenderCopy(Render, Texture, NULL, NULL);
		SDL_RenderPresent(Render);
		SDL_FreeSurface(TEMP);
		SDL_DestroyTexture(Texture);
		
	}


	inline SDL_Surface* IMGLoad(string Path)
	{
		SDL_Surface* Temp1 = IMG_Load(Path.c_str());
		if (Temp1==NULL)
		{
			EvSys->OnGraphicsError(IMG_GetError());
		}
		
		
		return Temp1;
	}
	void PreLoader(string PathToIMG)
	{
		PreLoadedPaths.push_back(PathToIMG);
		PreLoadedSurf.push_back(IMGLoad(PathToIMG));
	}

	SDL_Surface* AngleTransform(SDL_Surface* Source, float Angle)
	{
		//Transformation goes here!
		//OpenGL problems start here!
	}



	SDL_Surface* Loader(string Path)
	{
		SDL_Surface* Temp = NULL;
		bool SurfPresent = false;
		for (unsigned int i = 0; i < PreLoadedPaths.size(); i++)
		{
			if (PreLoadedPaths[i] == Path)
			{
				Temp = PreLoadedSurf[i];
				break;
			}
		}
		if (SurfPresent==false)

		{
			PreLoadedSurf.push_back(IMGLoad(Path));
			PreLoadedPaths.push_back(Path);
			Temp = PreLoadedSurf.back();
		}
		return Temp;
	}


};

