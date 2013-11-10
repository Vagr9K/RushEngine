#include <SDL.h>
#include "Eventing.h"
#include <iostream>
#include <string>

using namespace std;

class Graphics : public Eventing
{
private:
	int Width, Height, LayerNumber;
	char* Title;
	SDL_Window* main = NULL;
	SDL_Renderer *Render = NULL;
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

		return true;
	}

	bool Stop()
	{
		SDL_DestroyRenderer(Render);
		SDL_DestroyWindow(main);
		SDL_Quit();
		return true;
	}




};

