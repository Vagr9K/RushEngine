#include "GraphicsManager.h"

SDL_Texture * GraphicsManager::LoaderGPU (string Path)
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
void GraphicsManager::PreLoadGPU (string Path, bool CheckExistance)
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
void GraphicsManager::CleanPreLoadGPU (int IndexOfItem)
        {
		SDL_DestroyTexture(PreLoadedTextGPU->at(IndexOfItem));
		PreLoadedPathsGPU->erase(PreLoadedPathsGPU->begin() + IndexOfItem);
		PreLoadedTextGPU->erase(PreLoadedTextGPU->begin() + IndexOfItem);
	}
void GraphicsManager::ClearPreLoadGPU (double PartToClear)
        {
		unsigned int Size = PreLoadedPathsGPU->size();
		int Count = static_cast<int>(Size*PartToClear);
		for (int i = 0; i < Count;i++)
		{
			SDL_DestroyTexture(PreLoadedTextGPU->at(i));
		}

		PreLoadedTextGPU->erase(PreLoadedTextGPU->begin(), PreLoadedTextGPU->begin() + Count);
		PreLoadedPathsGPU->erase(PreLoadedPathsGPU->begin(), PreLoadedPathsGPU->begin() + Count);
	}