#include <SDL.h>
#include <SDL_image.h>
#include "Eventing.h"
#include <iostream>
#include <string>
#include <vector>
#include <SDL_opengl.h>

using namespace std;

class Graphics : public Eventing
{
private:
	int Width, Height, LayerNumber;
	const char* Title;
	SDL_Window* main = NULL;
	SDL_Renderer *Render = NULL;
	vector<SDL_Surface> PreLoadedSurf;
	vector<string> PreLoadedPaths;
public:
	Graphics(int Width, int Height, int LayerNumber,string Title)
	{
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title.c_str();
	}
	
	bool Start()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			OnGraphicsError(SDL_GetError());
			return false;
		}
		main = SDL_CreateWindow(Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_SHOWN);
		if (main==NULL)
		{
			OnGraphicsError(SDL_GetError());
			return false;
		}
		Render = SDL_CreateRenderer(main, -1, SDL_RENDERER_ACCELERATED);
		if (Render==NULL)
		{
			OnGraphicsError(SDL_GetError());
			return false;
		}

		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat&IMGFlags != IMGFlags)
		{
			OnGraphicsError(IMG_GetError());
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

	inline SDL_Surface IMGLoad(string Path)
	{
		SDL_Surface* Temp1 = IMG_Load(Path.c_str());
		SDL_Surface Temp = *Temp1;
		delete Temp1;
		return Temp;
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



	void Loader(int x, int y, int h, int w, string Path)
	{
		SDL_Surface Temp;
		bool SurfPresent = false;
		for (int i = 0; i < PreLoadedPaths.size(); i++)
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

		//Add more code


	}


};

