#include "GraphicsManager.h"

void GraphicsManager::SetMaximumTimeOfText (int Time)
        {
		MaximumTimeFromLastUseOfText = Time;
	}
int GraphicsManager::GetMaximumTimeOfText ()
        {
		return MaximumTimeFromLastUseOfText;
	}

void GraphicsManager::CleanTextTextureGL (int IndexOfItem)
        {
		glDeleteTextures(1, &(LoadedTextsGL.at(IndexOfItem)).TextureID);
		LoadedTextsGL.erase(LoadedTextsGL.begin() + IndexOfItem);
		TimeFromLastUseGL.erase(TimeFromLastUseGL.begin() + IndexOfItem);
		LoadedTextArgsGL.erase(LoadedTextArgsGL.begin() + IndexOfItem);
	}
SDL_Surface * GraphicsManager::GetSurfaceSolid(TTF_Font * Font, string Text, SDL_Color Foreground)
{
	SDL_Surface* Surf = NULL;
	Surf = TTF_RenderText_Solid(Font, Text.c_str(), Foreground);
	if (Surf == NULL)
	{
		EventEngine->SystemEvents.GraphicsError(TTF_GetError());
	}
	return Surf;
}

TTF_Font * GraphicsManager::LoadFont (string FontPath, int PointSize, int Index)
        {
		TTF_Font* Font = NULL;
		if (Index == 0)
		{
			Font = TTF_OpenFont(FontPath.c_str(), PointSize);
			if (Font == NULL)
			{
				EventEngine->SystemEvents.GraphicsError(TTF_GetError());

			}
			return Font;
		}
		else
		{
			Font = TTF_OpenFontIndex(FontPath.c_str(), PointSize, Index);
			if (Font == NULL)
			{
				EventEngine->SystemEvents.GraphicsError(TTF_GetError());

			}
			return Font;
		}
		return Font;

	}
TTF_Font * GraphicsManager::GetFont (string FontPath, int PointSize, int FontOutline, Style FontStyle, int Index, bool FontKerning)
        {
		TTF_Font* Font = NULL;
		bool Found = false;
		string Path = FontPath + to_string(static_cast<long long>(PointSize)) + to_string(static_cast<long long>(Index));
		for (unsigned int i = 0; i < LoadedFontsPaths.size(); i++)
		{
			if (LoadedFontsPaths.at(i) == Path)
			{
				Font = LoadedFonts.at(i);
				Found = true;
				break;
			}
		}



		if (Found == false)
			Font = LoadFont(FontPath, PointSize, Index);
		if (FontOutline != 0)
		{
			TTF_SetFontOutline(Font, FontOutline);

		}
		if (FontKerning == true)
		{
			TTF_SetFontKerning(Font, 1);
		}
		switch (FontStyle)
		{
		case NORMAL:
			TTF_SetFontStyle(Font, TTF_STYLE_NORMAL);
			break;
		case BOLD:
			TTF_SetFontStyle(Font, TTF_STYLE_BOLD);
			break;
		case ITALIC:
			TTF_SetFontStyle(Font, TTF_STYLE_ITALIC);
			break;
		case STRIKETHROUGH:
			TTF_SetFontStyle(Font, TTF_STYLE_STRIKETHROUGH);
			break;
		case UNDERLINE:
			TTF_SetFontStyle(Font, TTF_STYLE_UNDERLINE);
			break;
		default:
			break;
		}
		if (Found == false)
		{
			LoadedFonts.push_back(Font);
			LoadedFontsPaths.push_back(Path);
		}
		return Font;

	}
SDL_Surface * GraphicsManager::GetSurfaceShaded(TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background)
{
	SDL_Surface* Surf = NULL;
	Surf = TTF_RenderText_Shaded(Font, Text.c_str(), Foreground, Background);
	if (Surf == NULL)
	{
		EventEngine->SystemEvents.GraphicsError(TTF_GetError());
	}
	return Surf;
}
TextureInfo GraphicsManager::GetTextImageGL(TextFont * Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background)
        {
		TextureInfo Texture;
		string args = to_string(static_cast<long long>(Font->FontKerning)) + to_string(static_cast<long long>(Font->FontOutline))
			+ Font->FontPath + to_string(static_cast<long long>(Font->FontStyle)) + to_string(static_cast<long long>(Font->Index))
			+ to_string(static_cast<long long>(Font->PointSize)) + Text;
		for (unsigned int i = 0; i < TimeFromLastUseGL.size(); i++)
		{
			if (LoadedTextArgsGL.at(i) == args)
			{

				TimeFromLastUseGL.at(i) = 0;
				return LoadedTextsGL.at(i);
				Texture = LoadedTextsGL.at(i);
				break;
			}
			else
			{
				if (TimeFromLastUseGL.at(i) >= MaximumTimeFromLastUseOfText)
				{
					CleanTextTextureGL(i);
					i--;

				}
				else
				{
					TimeFromLastUseGL.at(i)++;
				}
			}
		}
		TTF_Font* TTFFONT = GetFont(Font->FontPath, Font->PointSize, Font->FontOutline, Font->FontStyle, Font->Index, Font->FontKerning);
		switch (DrawMode)
		{
		case SOLID:
			Texture = GetTextureSolidGL(TTFFONT, Text, Foregroung);
			break;
			/*
		case SHADED:
			Texture = GetTextureShadedGL(TTFFONT, Text, Foregroung, Background); //No support for SHADED mode!
			break;
			*/
		case BLENDED:
			Texture = GetTextureBlendedGL(TTFFONT, Text, Foregroung);
			break;
		default:
			EventEngine->SystemEvents.GraphicsError("Undefined drawing mode passed to GetTextImageGL() function.");
			break;
		}
		LoadedTextsGL.push_back(Texture);
		TimeFromLastUseGL.push_back(0);
		LoadedTextArgsGL.push_back(args);



		return Texture;
	}
SDL_Surface * GraphicsManager::GetSurfaceBlended (TTF_Font * Font, string Text, SDL_Color Foreground)
        {
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Blended(Font, Text.c_str(), Foreground);
		if (Surf == NULL)
		{
			EventEngine->SystemEvents.GraphicsError(TTF_GetError());
		}
		return Surf;
	}
TextureInfo GraphicsManager::GetTextureBlendedGL(TTF_Font * Font, string Text, SDL_Color Foreground)
        {
		SDL_Surface* TMPSURF = GetSurfaceBlended(Font, Text, Foreground);
		TextureInfo Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}
TextureInfo GraphicsManager::GetTextureSolidGL(TTF_Font * Font, string Text, SDL_Color Foreground)
        {
		SDL_Surface* TMPSURF = GetSurfaceSolid(Font, Text, Foreground);
		TextureInfo Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}
TextureInfo GraphicsManager::GetTextureShadedGL(TTF_Font * Font, string Text, SDL_Color Foreground, SDL_Color Background)
        {
		SDL_Surface* TMPSURF = GetSurfaceShaded(Font, Text, Foreground, Background);
		TextureInfo Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}