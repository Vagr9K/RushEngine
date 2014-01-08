#include "GraphicsManager.h"

int GraphicsManager::GetNearestPowerOfTwo(int OldNumber)
{
	if (OldNumber != 0)
	{
		OldNumber--;
		OldNumber |= (OldNumber >> 1); 
		OldNumber |= (OldNumber >> 2); 
		OldNumber |= (OldNumber >> 4); 
		OldNumber |= (OldNumber >> 8); 
		OldNumber |= (OldNumber >> 16); 
		OldNumber++;
	}

	return OldNumber;
}



TextureInfo GraphicsManager::GenerateTexture (SDL_Surface * Surface)
        {
		bool TwoError = false;
		bool CleanSurface = false;
		GLuint Texture;
		GLuint Colors = 4;
		GLenum IMGFormat = (GLenum)NULL;
		int ImageW, ImageH, TextureW, TextureH;
		GLfloat KX = 1.f, KY = 1.f;
#define PowerChecker(n) !(n&(n-1))
		if (!PowerChecker(Surface->w) || !PowerChecker(Surface->h))
		{
			
			ImageW = Surface->w;
			ImageH = Surface->h;
			TextureW = GetNearestPowerOfTwo(ImageW);
			TextureH = GetNearestPowerOfTwo(ImageH);
			KX = (GLfloat)ImageW / (GLfloat)TextureW;
			KY = (GLfloat)ImageH / (GLfloat)TextureH;
			/*
			Uint32 MinPixel = SDL_MapRGB(Surface->format, 0, 0, 0);
			Uint32* NewPixelArray = new Uint32[TextureH*TextureW];
			Uint32* PixelArray = (Uint32*)Surface->pixels;


			
			unsigned int OldIter = 0;
			unsigned int NewIter = 0;
			for (int i = 0; i < ImageH; i++)
			{
				for (int j = 0; j < ImageW; j++)
				{

					NewPixelArray[NewIter] = PixelArray[OldIter];
					NewIter++;
					OldIter++;
				}
				for (int k = 0; k < TextureW - ImageW; k++)
				{
					NewPixelArray[NewIter] = MinPixel;
					NewIter++;
				}

			}
			unsigned int NewIterMax = TextureW*TextureH;
			while (NewIter < NewIterMax)
			{
				NewPixelArray[NewIter] = MinPixel;
				NewIter++;
			}
			Surface->pixels = NewPixelArray;
			*/
			SDL_Color Background = { 0, 0, 0, 0 };
			SDL_SetSurfaceAlphaMod(Surface, 0xFF);
			//SDL_SetSurfaceBlendMode(Surface, SDL_BLENDMODE_BLEND);
			SDL_Rect BlitArea;
			BlitArea.h = ImageH;
			BlitArea.w = ImageW;
			BlitArea.x = 0;
			BlitArea.y = 0;
			Uint32 rmask, amask, gmask, bmask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
			rmask = 0xff000000;
			gmask = 0x00ff0000;
			bmask = 0x0000ff00;
			amask = 0x000000ff;
#else
			rmask = 0x000000ff;
			gmask = 0x0000ff00;
			bmask = 0x00ff0000;
			amask = 0xff000000;
#endif

			SDL_Surface *NewSurf = SDL_CreateRGBSurface(0, TextureW, TextureH, 32, rmask, gmask, bmask, amask);

			if (NewSurf == NULL)
			{
				EventEngine->SystemEvents.GraphicsError("Can't create new surface for OpenGL in function GenerateTexture().");
			}

			SDL_BlitSurface(Surface, &BlitArea, NewSurf, NULL);

			
			Surface = NewSurf;
			CleanSurface = true;
			
		}
		else
		{
			TextureW = Surface->w;
			TextureH = Surface->h;
		}
		Colors = Surface->format->BytesPerPixel;
		if (Colors == 4)
		{
			IMGFormat = GL_RGBA;
		} 
		else if (Colors == 3)
		{
			IMGFormat = GL_RGB;
		}
		else
		{
			IMGFormat = GL_RGBA;
			TwoError = true;
			
		}
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, Colors, TextureW, TextureH, 0, IMGFormat, GL_UNSIGNED_BYTE, Surface->pixels);

		if (glGetError() != GL_NO_ERROR)
		{   if (TwoError)
			{
				EventEngine->SystemEvents.GraphicsError("Image format not supported at function GenerateTexture().");
			}
			EventEngine->SystemEvents.GraphicsError("OpenGL error in function GenerateTexture() : " + glGetError());
			
			
		}
		TextureInfo TextureData;
		TextureData.KxKy.KX = KX;
		TextureData.KxKy.KY = KY;
		TextureData.TextureID = Texture;
		if (CleanSurface)
			SDL_FreeSurface(Surface);
		return TextureData;

	}
TextureInfo GraphicsManager::GenerateTexture(string Path)
        {
		SDL_Surface* TMPSURF = NULL;
		TMPSURF = IMGLoad(Path);
		TextureInfo TextureData = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return TextureData;
	}
TextureInfo GraphicsManager::LoaderGL(string Path)
        {
		TextureInfo Temp;
		bool TextPresent = false;
		for (unsigned int i = 0; i < PreLoadedPathsGL->size(); i++)
		{
			if (PreLoadedPathsGL->at(i) == Path)
			{
				Temp = PreLoadedTextGL->at(i);
				TextPresent = true;
				break;
			}
		}
		if (TextPresent == false)

		{
			PreLoadedTextGL->push_back(GenerateTexture(Path));
			PreLoadedPathsGL->push_back(Path);
			Temp = PreLoadedTextGL->back();
		}
		return Temp;
	}
void GraphicsManager::CleanPreLoadGL (int IndexOfItem)
        {
		glDeleteTextures(1,&(PreLoadedTextGL->at(IndexOfItem)).TextureID);
		PreLoadedPathsGL->erase(PreLoadedPathsGL->begin() + IndexOfItem);
		PreLoadedTextGL->erase(PreLoadedTextGL->begin() + IndexOfItem);
	}
void GraphicsManager::ClearPreLoadGL (double PartToClear)
        {
		unsigned int Size = PreLoadedPathsGL->size();
		int Count = static_cast<int>(Size*PartToClear);
		TextureInfo* TextureToDelete = new TextureInfo[Count];
		for (int i = 0; i < Count;i++)
		{
			TextureToDelete[i] = PreLoadedTextGL->at(i);
		}
		glDeleteTextures(Count, &TextureToDelete->TextureID);
		PreLoadedTextGL->erase(PreLoadedTextGL->begin(), PreLoadedTextGL->begin() + Count);
		PreLoadedPathsGL->erase(PreLoadedPathsGL->begin(), PreLoadedPathsGL->begin() + Count);
	}
