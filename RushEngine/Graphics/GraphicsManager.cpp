#include "GraphicsManager.h"
#include "SDL_image.h"
void GraphicsManager::InitOldCpp ()
        {
		PreLoadedSurfCPU = NULL;
		PreLoadedTextGPU = NULL;
		PreLoadedPathsCPU = NULL;
		PreLoadedPathsGPU = NULL;
		PreLoadedPathsGL = NULL;
		PreLoadedTextGL = NULL;
		EventEngine = NULL;
		Renderer = NULL;
		OptimalObjectCount = 0;
		MaximumTimeFromLastUseOfText = 0;
	}
GraphicsManager::GraphicsManager (EventingEngine * EventEngine, SDL_Renderer * Renderer, vector <SDL_Surface*> * PreLoadedSurfCPU, vector <SDL_Texture*> * PreLoadedTextGPU, vector <GLuint> * PreLoadedTextGL, vector <string> * PreLoadedPathsCPU, vector <string> * PreLoadedPathsGPU, vector <string> * PreLoadedPathsGL)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		this->PreLoadedPathsCPU = PreLoadedPathsCPU;
		this->PreLoadedPathsGPU = PreLoadedPathsGPU;
		this->PreLoadedPathsGL = PreLoadedPathsGL;
		this->PreLoadedSurfCPU = PreLoadedSurfCPU;
		this->PreLoadedTextGPU = PreLoadedTextGPU;
		this->PreLoadedTextGL = PreLoadedTextGL;
	}
GraphicsManager::GraphicsManager (EventingEngine * EventEngine, SDL_Renderer * Renderer)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		InitPreloaders();
	}
GraphicsManager::GraphicsManager (EventingEngine * EventEngine, SDL_Renderer * Renderer, int OptimalObjectCount)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		this->OptimalObjectCount = OptimalObjectCount;
		InitPreloaders();
	}
void GraphicsManager::SetOptimalObjectCount (int OptimalObjectCount)
        {
		this->OptimalObjectCount = OptimalObjectCount;
	}
int GraphicsManager::GetOptimalObjectCount ()
        {
		return this->OptimalObjectCount;
	}

void GraphicsManager::InitPreloaders ()
        {
		if (PreLoadedPathsCPU != NULL)
		{
			delete[] PreLoadedPathsCPU;
		}
		if (PreLoadedPathsGPU != NULL)
		{
			delete[] PreLoadedPathsGPU;
		}
		if (PreLoadedPathsGL != NULL)
		{
			delete[] PreLoadedPathsGL;
		}
		if (PreLoadedSurfCPU != NULL)
		{
			delete[] PreLoadedSurfCPU;
		}
		if (PreLoadedTextGPU != NULL)
		{
			delete[] PreLoadedTextGPU;
		}
		if (PreLoadedTextGL != NULL)
		{
			delete[] PreLoadedTextGL;
		}
		this->PreLoadedPathsCPU = new vector<string>(OptimalObjectCount);
		this->PreLoadedPathsGPU = new vector<string>(OptimalObjectCount);
		this->PreLoadedPathsGL = new vector<string>(OptimalObjectCount);
		this->PreLoadedSurfCPU = new vector <SDL_Surface*>(OptimalObjectCount);
		this->PreLoadedTextGPU = new vector<SDL_Texture*>(OptimalObjectCount);
		this->PreLoadedTextGL = new vector<GLuint>(OptimalObjectCount);
	}



SDL_Surface * GraphicsManager::IMGLoad (string Path)
        {
		SDL_Surface* Surface = IMG_Load(Path.c_str());
		if (Surface == NULL)
		{
			EventEngine->SystemEvents.GraphicsError(IMG_GetError());
		}


		return Surface;
	}


