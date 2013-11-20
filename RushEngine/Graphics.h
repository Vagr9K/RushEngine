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

class GraphicsEngine
{

	
private:
	int Width, Height, LayerNumber;
	char Title;
	bool IsReady = false; 
	bool IsStarted = false;
	SDL_Window* main = NULL;
	SDL_Renderer *Render = NULL;
	vector<SDL_Surface*> PreLoadedSurfCPU;
	vector<SDL_Texture*> PreLoadedTextGPU;
	vector<string> PreLoadedPathsCPU;
	vector<string> PreLoadedPathsGPU;
	GEEventing* EvSys;
	SDL_Surface* TEMP;
	
public:
	
	
	
	GraphicsEngine(){}
	GraphicsEngine(int Width, int Height, int LayerNumber,string Title, GEEventing* EvVar)
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


		IsStarted = true;
		return true;
	}

	bool Stop()
	{
		SDL_DestroyRenderer(Render);
		SDL_DestroyWindow(main);
		IMG_Quit();
		SDL_Quit();
		IsStarted = false;
		return true;
	}
	void DelayGraphics(int Milliseconds)
	{
		SDL_Delay(Milliseconds);
	}

	void BlackInit()
	{
		SDL_Texture* Texture = LoaderGPU("images/BlackInit.png");
		SDL_RenderClear(Render);
		SDL_RenderCopy(Render, Texture, NULL, NULL);
		SDL_RenderPresent(Render);
		
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
	void PreLoaderCPU(string PathToIMG)
	{
		PreLoadedPathsCPU.push_back(PathToIMG);
		PreLoadedSurfCPU.push_back(IMGLoad(PathToIMG));
	}

	void PreLoaderGPU(string PathToIMG)
	{
		PreLoadedPathsGPU.push_back(PathToIMG);
		PreLoadedTextGPU.push_back(SDL_CreateTextureFromSurface(Render, IMGLoad(PathToIMG)));
	}




	SDL_Surface* LoaderCPU(string Path)
	{
		SDL_Surface* Temp = NULL;
		bool SurfPresent = false;
		for (unsigned int i = 0; i < PreLoadedPathsCPU.size(); i++)
		{
			if (PreLoadedPathsCPU[i] == Path)
			{
				Temp = PreLoadedSurfCPU[i];
				SurfPresent = true;
				break;
			}
		}
		if (SurfPresent==false)

		{
			PreLoadedSurfCPU.push_back(IMGLoad(Path));
			PreLoadedPathsCPU.push_back(Path);
			Temp = PreLoadedSurfCPU.back();
		}
		return Temp;
	}

	SDL_Texture* LoaderGPU(string Path)
	{
		SDL_Texture* Temp = NULL;
		bool TextPresent = false;
		for (unsigned int i = 0; i < PreLoadedPathsGPU.size(); i++)
		{
			if (PreLoadedPathsGPU[i] == Path)
			{
				Temp = PreLoadedTextGPU[i];
				TextPresent = true;
				break;
			}
		}
		if (TextPresent == false)

		{
			PreLoadedTextGPU.push_back(SDL_CreateTextureFromSurface(Render, IMGLoad(Path)));
			PreLoadedPathsGPU.push_back(Path);
			Temp = PreLoadedTextGPU.back();
		}
		return Temp;
	}
	//Define function of power of 2 check for OpenGl texture creation compatibility
#define ISPWR2(n) !(n&(n-1))
	bool DrawImageGPUSingle(int X, int Y, int H, int W, float Angle, string Path) //Experimental function, may be removed later.
	{
		SDL_Surface* Image = LoaderCPU(Path);
 //Must be power of 2!! (2,4,8,16,32,64,128,256...)
		if (ISPWR2(Image->h) || ISPWR2(Image->w))
		{
			EvSys->OnGraphicsError("Image: "+Path+"\n" + "Width or Height is not power of 2.");
			return false;
		}
		 Uint8 Colours = Image->format->BytesPerPixel;
		 GLuint Format;
		 if (Colours==4)
		 {
			 Format = GL_RGBA;
		 } 
		 else if (Colours==3)
		 {
			 Format = GL_RGB;
		 }
		 else
		 {
			 EvSys->OnGraphicsError("Image: " + Path + "\n" + "Format is not recognized.");
			 return false;
		 }

		 GLuint Texture;
		 glGenTextures(1, &Texture);
		 glBindTexture(GL_TEXTURE_2D, Texture);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		 glTexImage2D(GL_TEXTURE_2D, 0, Format, Image->w, Image->h, 0, Format, GL_UNSIGNED_BYTE, Image->pixels);

		 glClear(GL_COLOR_BUFFER_BIT);
		 glTranslatef(X, Y, 0);
		 glRotatef(Angle, 0.0, 0.0, 1.0);
		 glBindTexture(GL_TEXTURE_2D, Texture);
		 //Non-OpenGL ES code!. Must be replaced.
		 glBegin(GL_QUADS);

		//Unfinished function!!!!!!!!


	}

};

