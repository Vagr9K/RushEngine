#include "GraphicsManager.h"

GLuint GraphicsManager::GenerateTexture (SDL_Surface * Surface)
        {
		GLuint Texture;
		GLuint Colors = 0;
		GLenum IMGFormat = (GLenum)NULL;
		
#define PowerChecker(n) !(n&(n-1))
		if (!PowerChecker(Surface->w) || !PowerChecker(Surface->h))
		{
			EventEngine->GraphicsError("Image size is not a power of 2 at function GenerateTexture().");
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
			EventEngine->GraphicsError("Image format not supported at function GenerateTexture().");
		}
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, Colors, Surface->w, Surface->h, 0, IMGFormat, GL_UNSIGNED_BYTE, Surface->pixels);

		if (glGetError() != GL_NO_ERROR)
		{
			EventEngine->GraphicsError("OpenGL error in function GenerateTexture() : " + glGetError());
		}
		return Texture;

	}
GLuint GraphicsManager::GenerateTexture (string Path)
        {
		SDL_Surface* TMPSURF = NULL;
		TMPSURF = IMGLoad(Path);
		GLuint Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}
GLuint GraphicsManager::LoaderGL (string Path)
        {
		GLuint Temp = NULL;
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
		glDeleteTextures(1,&(PreLoadedTextGL->at(IndexOfItem)));
		PreLoadedPathsGL->erase(PreLoadedPathsGL->begin() + IndexOfItem);
		PreLoadedTextGL->erase(PreLoadedTextGL->begin() + IndexOfItem);
	}
void GraphicsManager::ClearPreLoadGL (double PartToClear)
        {
		unsigned int Size = PreLoadedPathsGL->size();
		int Count = static_cast<int>(Size*PartToClear);
		GLuint* TextureToDelete = new GLuint[Count];
		for (int i = 0; i < Count;i++)
		{
			TextureToDelete[i] = PreLoadedTextGL->at(i);
		}
		glDeleteTextures(Count, TextureToDelete);
		PreLoadedTextGL->erase(PreLoadedTextGL->begin(), PreLoadedTextGL->begin() + Count);
		PreLoadedPathsGL->erase(PreLoadedPathsGL->begin(), PreLoadedPathsGL->begin() + Count);
	}
