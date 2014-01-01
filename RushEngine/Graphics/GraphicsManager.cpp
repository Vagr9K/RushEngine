#include "GraphicsManager.h"
#include "SDL_image.h"
void GraphicsManager::InitOldCpp ()
        {
		PreLoadedPathsGL = NULL;
		PreLoadedTextGL = NULL;
		EventEngine = NULL;
		OptimalObjectCount = 0;
		MaximumTimeFromLastUseOfText = 0;
	}
GraphicsManager::GraphicsManager(EventingEngine * EventEngine, vector <TextureInfo> * PreLoadedTextGL, vector <string> * PreLoadedPathsGL)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->PreLoadedPathsGL = PreLoadedPathsGL;
		this->PreLoadedTextGL = PreLoadedTextGL;
	}
GraphicsManager::GraphicsManager (EventingEngine * EventEngine)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		InitPreloaders();
	}
GraphicsManager::GraphicsManager (EventingEngine * EventEngine, int OptimalObjectCount)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
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
		if (PreLoadedPathsGL != NULL)
		{
			delete[] PreLoadedPathsGL;
		}
		if (PreLoadedTextGL != NULL)
		{
			delete[] PreLoadedTextGL;
		}
		
		this->PreLoadedPathsGL = new vector<string>(OptimalObjectCount);
		this->PreLoadedTextGL = new vector<TextureInfo>(OptimalObjectCount);
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


