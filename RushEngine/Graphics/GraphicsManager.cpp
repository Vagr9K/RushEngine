#include "GraphicsManager.h"
#include "SDL_image.h"
void GraphicsManager::InitOldCpp ()
        {
		PreLoadedPathsGL = NULL;
		PreLoadedTextGL = NULL;
		EventEngine = NULL;
		OptimalObjectCount = 0;
		MaximumTimeFromLastUseOfText = 0;
		ObjEngine = NULL;
	}
GraphicsManager::GraphicsManager(EventingEngine * EventEngine, ObjectsEngine* ObjEngine, vector <TextureInfo> * PreLoadedTextGL, vector <string> * PreLoadedPathsGL)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->PreLoadedPathsGL = PreLoadedPathsGL;
		this->PreLoadedTextGL = PreLoadedTextGL;
		this->ObjEngine = ObjEngine;
	}
GraphicsManager::GraphicsManager(EventingEngine * EventEngine, ObjectsEngine* ObjEngine)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->ObjEngine = ObjEngine;
		InitPreloaders();
	}
GraphicsManager::GraphicsManager(EventingEngine * EventEngine, ObjectsEngine* ObjEngine, int OptimalObjectCount)
        {
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->OptimalObjectCount = OptimalObjectCount;
		this->ObjEngine = ObjEngine;
		InitPreloaders();
	}
ObjectsEngine* GraphicsManager::GetObjEngine()
{
	return this->ObjEngine;
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


