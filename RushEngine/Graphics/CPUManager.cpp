#include "GraphicsManager.h"

SDL_Surface * GraphicsManager::LoaderCPU (string Path)
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
bool GraphicsManager::PreLoadCPU (string Path, bool CheckExistance)
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

	void GraphicsManager::CleanPreLoadCPU (int IndexOfItem)
        {
		SDL_FreeSurface(PreLoadedSurfCPU->at(IndexOfItem));
		PreLoadedPathsCPU->erase(PreLoadedPathsCPU->begin() + IndexOfItem);
		PreLoadedSurfCPU->erase(PreLoadedSurfCPU->begin() + IndexOfItem);
	}
void GraphicsManager::ClearPreLoadCPU (double PartToClear)
        {
		unsigned int Size = PreLoadedPathsCPU->size();
		int Count = static_cast<int>(Size*PartToClear);
		for (int i = 0; i < Count;i++)
		{
			SDL_FreeSurface(PreLoadedSurfCPU->at(i));
		}

		PreLoadedSurfCPU->erase(PreLoadedSurfCPU->begin(), PreLoadedSurfCPU->begin() + Count);
		PreLoadedPathsCPU->erase(PreLoadedPathsCPU->begin(), PreLoadedPathsCPU->begin() + Count);
	}

	