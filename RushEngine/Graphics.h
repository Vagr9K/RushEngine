#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "Eventing.h"
//Platform dependent includes!
#ifdef __WINDOWS__
#include <gl/GLU.h>
#elif __ANDROID__
//Android includes here!

#endif // __WINDOWS__



using namespace std;
enum Mode
{
	SOLID,
	SHADED,
	BLENDED,

};
enum Style

{
	NORMAL,
	BOLD,
	ITALIC,
	STRIKETHROUGH,
	UNDERLINE

};
class GameEngine;

struct TextFont
{


	string FontPath;
	int PointSize;
	int FontOutline;
	Style FontStyle;
	int Index;
	bool FontKerning;
private:
	void InitOldCpp()
	{
		PointSize=12;
		FontOutline =0;
		FontStyle = NORMAL;
		Index = 0;
		FontKerning = false;
	}


public:

	TextFont(string FontPath)
	{
		InitOldCpp();
		this->FontPath = FontPath;

	}
};


class GraphicsManager
{

	vector<SDL_Surface*>* PreLoadedSurfCPU;
	vector<SDL_Texture*>* PreLoadedTextGPU;
	vector<string>* PreLoadedPathsCPU;
	vector<string>* PreLoadedPathsGPU;
	EventingEngine* EventEngine;
	SDL_Renderer* Renderer;
	int OptimalObjectCount;

	vector<TTF_Font*> LoadedFonts;
	vector<string> LoadedFontsPaths;
	vector<SDL_Surface*> LoadedTextsCPU;
	vector<string> LoadedTextArgsCPU;
	vector<string> LoadedTextArgsGPU;
	vector<string> LoadedTextArgsGL;
	vector<SDL_Texture*> LoadedTextsGPU;
	vector<GLuint> LoadedTextsGL;
	vector<int> TimeFromLastUseCPU;
	vector<int> TimeFromLastUseGPU;
	vector<int> TimeFromLastUseGL;
	int MaximumTimeFromLastUseOfText;
	vector<string>* PreLoadedPathsGL;
	vector<GLuint>* PreLoadedTextGL;
private:
	void InitOldCpp()
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


public:
	GraphicsManager(EventingEngine *EventEngine, SDL_Renderer* Renderer,
		vector<SDL_Surface*>* PreLoadedSurfCPU, vector<SDL_Texture*>* PreLoadedTextGPU, vector<GLuint>* PreLoadedTextGL,
		vector<string>* PreLoadedPathsCPU, vector<string>* PreLoadedPathsGPU, vector<string>* PreLoadedPathsGL)
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
	GraphicsManager(EventingEngine *EventEngine, SDL_Renderer* Renderer)
	{
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		InitPreloaders();
	}
	GraphicsManager(EventingEngine *EventEngine, SDL_Renderer* Renderer, int OptimalObjectCount)
	{
		InitOldCpp();
		this->EventEngine = EventEngine;
		this->Renderer = Renderer;
		this->OptimalObjectCount = OptimalObjectCount;
		InitPreloaders();
	}

	void SetOptimalObjectCount(int OptimalObjectCount)
	{
		this->OptimalObjectCount = OptimalObjectCount;
	}

	int GetOptimalObjectCount()
	{
		return this->OptimalObjectCount;
	}
	void SetMaximumTimeOfText(int Time)
	{
		MaximumTimeFromLastUseOfText = Time;
	}
	int GetMaximumTimeOfText()
	{
		return MaximumTimeFromLastUseOfText;
	}

	void InitPreloaders()
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



	void CleanTextSurfaceCPU(int IndexOfItem)
	{
		SDL_FreeSurface(LoadedTextsCPU.at(IndexOfItem));
		LoadedTextsCPU.erase(LoadedTextsCPU.begin() + IndexOfItem);
		TimeFromLastUseCPU.erase(TimeFromLastUseCPU.begin() + IndexOfItem);
		LoadedTextArgsCPU.erase(LoadedTextArgsCPU.begin() + IndexOfItem);
	}
	void CleanTextTextureGPU(int IndexOfItem)
	{
		SDL_DestroyTexture(LoadedTextsGPU.at(IndexOfItem));
		LoadedTextsGPU.erase(LoadedTextsGPU.begin() + IndexOfItem);
		TimeFromLastUseGPU.erase(TimeFromLastUseGPU.begin() + IndexOfItem);
		LoadedTextArgsGPU.erase(LoadedTextArgsGPU.begin() + IndexOfItem);
	}

	void CleanTextTextureGL(int IndexOfItem)
	{
		glDeleteTextures(1, &(LoadedTextsGL.at(IndexOfItem)));
		LoadedTextsGL.erase(LoadedTextsGL.begin() + IndexOfItem);
		TimeFromLastUseGL.erase(TimeFromLastUseGL.begin() + IndexOfItem);
		LoadedTextArgsGL.erase(LoadedTextArgsGL.begin() + IndexOfItem);
	}

	TTF_Font* LoadFont(string FontPath, int PointSize, int Index = 0)
	{
		TTF_Font* Font = NULL;
		if (Index == 0)
		{
			Font = TTF_OpenFont(FontPath.c_str(), PointSize);
			if (Font == NULL)
			{
				EventEngine->GraphicsError(TTF_GetError());

			}
			return Font;
		}
		else
		{
			Font = TTF_OpenFontIndex(FontPath.c_str(), PointSize, Index);
			if (Font == NULL)
			{
				EventEngine->GraphicsError(TTF_GetError());

			}
			return Font;
		}
		return Font;

	}

	TTF_Font* GetFont(string FontPath, int PointSize, int FontOutline, Style FontStyle, int Index = 0, bool FontKerning = false)
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



	SDL_Surface* GetTextImageCPU(TextFont* Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background)
	{
		SDL_Surface* Surf = NULL;
		string args = to_string(static_cast<long long>(Font->FontKerning)) + to_string(static_cast<long long>(Font->FontOutline))
			+ Font->FontPath + to_string(static_cast<long long>(Font->FontStyle)) + to_string(static_cast<long long>(Font->Index))
			+ to_string(static_cast<long long>(Font->PointSize)) + Text;
		for (unsigned int i = 0; i < TimeFromLastUseCPU.size(); i++)
		{
			if (LoadedTextArgsCPU.at(i) == args)
			{

				TimeFromLastUseCPU.at(i) = 0;
				return LoadedTextsCPU.at(i);
				Surf = LoadedTextsCPU.at(i);
				break;
			}
			else
			{
				if (TimeFromLastUseCPU.at(i) >= MaximumTimeFromLastUseOfText)
				{
					CleanTextSurfaceCPU(i);
					i--;

				}
				else
				{
					TimeFromLastUseCPU.at(i)++;
				}
			}
		}
		TTF_Font* TTFFONT = GetFont(Font->FontPath, Font->PointSize, Font->FontOutline, Font->FontStyle, Font->Index, Font->FontKerning);
		switch (DrawMode)
		{
		case SOLID:
			Surf = GetSurfaceSolid(TTFFONT, Text, Foregroung);
			break;
		case SHADED:
			Surf = GetSurfaceShaded(TTFFONT, Text, Foregroung, Background);
			break;
		case BLENDED:
			Surf = GetSurfaceBlended(TTFFONT, Text, Foregroung);
			break;
		default:
			break;
		}
		LoadedTextsCPU.push_back(Surf);
		TimeFromLastUseCPU.push_back(0);
		LoadedTextArgsCPU.push_back(args);



		return Surf;
	}


	SDL_Texture* GetTextImageGPU(TextFont* Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background)
	{
		SDL_Texture* Texture = NULL;
		string args = to_string(static_cast<long long>(Font->FontKerning)) + to_string(static_cast<long long>(Font->FontOutline))
			+ Font->FontPath + to_string(static_cast<long long>(Font->FontStyle)) + to_string(static_cast<long long>(Font->Index))
			+ to_string(static_cast<long long>(Font->PointSize)) + Text;
		for (unsigned int i = 0; i < TimeFromLastUseGPU.size(); i++)
		{
			if (LoadedTextArgsGPU.at(i) == args)
			{

				TimeFromLastUseGPU.at(i) = 0;
				Texture = LoadedTextsGPU.at(i);
				return Texture;
				break;

			}
			else
			{
				if (TimeFromLastUseGPU.at(i) >= MaximumTimeFromLastUseOfText)
				{
					CleanTextTextureGPU(i);
					i--;

				}
				else
				{
					TimeFromLastUseGPU.at(i) = TimeFromLastUseGPU.at(i) + 1;
				}
			}
		}
		TTF_Font* TTFFONT = GetFont(Font->FontPath, Font->PointSize, Font->FontOutline, Font->FontStyle, Font->Index, Font->FontKerning);
		switch (DrawMode)
		{
		case SOLID:
			Texture = GetTextureSolid(TTFFONT, Text, Foregroung);
			break;
		case SHADED:
			Texture = GetTextureShaded(TTFFONT, Text, Foregroung, Background);
			break;
		case BLENDED:
			Texture = GetTextureBlended(TTFFONT, Text, Foregroung);
			break;
		default:
			break;
		}
		LoadedTextsGPU.push_back(Texture);
		TimeFromLastUseGPU.push_back(0);
		LoadedTextArgsGPU.push_back(args);



		return Texture;
	}
	GLuint GetTextImageGL(TextFont* Font, string Text, Mode DrawMode, SDL_Color Foregroung, SDL_Color Background)
	{
		GLuint Texture = NULL;
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
		case SHADED:
			Texture = GetTextureShadedGL(TTFFONT, Text, Foregroung, Background);
			break;
		case BLENDED:
			Texture = GetTextureBlendedGL(TTFFONT, Text, Foregroung);
			break;
		default:
			break;
		}
		LoadedTextsGL.push_back(Texture);
		TimeFromLastUseGL.push_back(0);
		LoadedTextArgsGL.push_back(args);



		return Texture;
	}


	SDL_Surface* GetSurfaceSolid(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Solid(Font, Text.c_str(), Foreground);
		if (Surf == NULL)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}
		return Surf;
	}
	SDL_Texture* GetTextureSolid(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* Surf = GetSurfaceSolid(Font, Text, Foreground);
		SDL_Texture* Texture = NULL;
		Texture = SDL_CreateTextureFromSurface(Renderer, Surf);
		if (Texture == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());
		}
		SDL_FreeSurface(Surf);
		return Texture;
	}

	SDL_Surface* GetSurfaceShaded(TTF_Font* Font, string Text, SDL_Color Foreground, SDL_Color Background)
	{
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Shaded(Font, Text.c_str(), Foreground, Background);
		if (Surf == NULL)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}
		return Surf;
	}
	SDL_Texture* GetTextureShaded(TTF_Font* Font, string Text, SDL_Color Foreground, SDL_Color Background)
	{
		SDL_Surface* Surf = GetSurfaceShaded(Font, Text, Foreground, Background);
		SDL_Texture* Texture = NULL;
		Texture = SDL_CreateTextureFromSurface(Renderer, Surf);
		if (Texture == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());
		}
		SDL_FreeSurface(Surf);
		return Texture;

	}


	SDL_Surface* GetSurfaceBlended(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* Surf = NULL;
		Surf = TTF_RenderText_Blended(Font, Text.c_str(), Foreground);
		if (Surf == NULL)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}
		return Surf;
	}
	GLuint GetTextureBlendedGL(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* TMPSURF = GetSurfaceBlended(Font, Text, Foreground);
		GLuint Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}
	SDL_Texture* GetTextureBlended(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* Surf = GetSurfaceBlended(Font, Text, Foreground);
		SDL_Texture* Texture = NULL;
		Texture = SDL_CreateTextureFromSurface(Renderer, Surf);
		if (Texture == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());
		}
		SDL_FreeSurface(Surf);
		return Texture;

	}
	GLuint GetTextureSolidGL(TTF_Font* Font, string Text, SDL_Color Foreground)
	{
		SDL_Surface* TMPSURF = GetSurfaceSolid(Font, Text, Foreground);
		GLuint Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}

	
	GLuint GetTextureShadedGL(TTF_Font* Font, string Text, SDL_Color Foreground, SDL_Color Background)
	{
		SDL_Surface* TMPSURF = GetSurfaceShaded(Font, Text, Foreground, Background);
		GLuint Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}

	SDL_Surface* LoaderCPU(string Path)
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

	bool PreLoadCPU(string Path, bool CheckExistance = true)
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
	void CleanPreLoadCPU(int IndexOfItem)
	{
		SDL_FreeSurface(PreLoadedSurfCPU->at(IndexOfItem));
		PreLoadedPathsCPU->erase(PreLoadedPathsCPU->begin() + IndexOfItem);
		PreLoadedSurfCPU->erase(PreLoadedSurfCPU->begin() + IndexOfItem);
	}
	void ClearPreLoadCPU(double PartToClear)
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





	SDL_Surface* IMGLoad(string Path)
	{
		SDL_Surface* Surface = IMG_Load(Path.c_str());
		if (Surface == NULL)
		{
			EventEngine->GraphicsError(IMG_GetError());
		}


		return Surface;
	}
	SDL_Texture* LoaderGPU(string Path)
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
	void PreLoadGPU(string Path, bool CheckExistance = true)
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
	void CleanPreLoadGPU(int IndexOfItem)
	{
		SDL_DestroyTexture(PreLoadedTextGPU->at(IndexOfItem));
		PreLoadedPathsGPU->erase(PreLoadedPathsGPU->begin() + IndexOfItem);
		PreLoadedTextGPU->erase(PreLoadedTextGPU->begin() + IndexOfItem);
	}
	void ClearPreLoadGPU(double PartToClear)
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
	GLuint GenerateTexture(SDL_Surface* Surface)
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
	GLuint GenerateTexture(string Path)
	{
		SDL_Surface* TMPSURF = NULL;
		TMPSURF = IMGLoad(Path);
		GLuint Texture = GenerateTexture(TMPSURF);
		SDL_FreeSurface(TMPSURF);
		return Texture;
	}


	GLuint LoaderGL(string Path)
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
	void CleanPreLoadGL(int IndexOfItem)
	{
		glDeleteTextures(1,&(PreLoadedTextGL->at(IndexOfItem)));
		PreLoadedPathsGL->erase(PreLoadedPathsGL->begin() + IndexOfItem);
		PreLoadedTextGL->erase(PreLoadedTextGL->begin() + IndexOfItem);
	}
	void ClearPreLoadGL(double PartToClear)
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


};



class DrawCPU
{


	SDL_Window* Window;
	SDL_Surface* WinSurf;
	SDL_Rect CopyFrom;
	SDL_Rect CopyTo;
	GraphicsManager* ManagerGR;
private:
	void InitOldCpp()
	{
		Window = NULL;
		WinSurf = NULL;
		ManagerGR = NULL;
	}

public:
	DrawCPU(GraphicsManager* ManagerGR, SDL_Window* mainWindow)
	{
		InitOldCpp();
		this->Window = mainWindow;
		this->ManagerGR = ManagerGR;
		WinSurf = SDL_GetWindowSurface(Window);

	}
	~DrawCPU()
	{
		ClearAll();

	}


	void StartBuffer()
	{
		SDL_FillRect(WinSurf, NULL, SDL_MapRGB(WinSurf->format, 0, 0, 0));
	}


	void AddToBuffer(int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source)
	{
		CopyFrom.h = OrigH;
		CopyFrom.w = OrigW;
		CopyFrom.x = OrigX;
		CopyFrom.y = OrigY;
		CopyTo.h = CopyH;
		CopyTo.w = CopyW;
		CopyTo.x = CopyX;
		CopyTo.y = CopyY;
		SDL_BlitSurface(ManagerGR->LoaderCPU(Source), &CopyFrom, WinSurf, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Source)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->LoaderCPU(Source), NULL, WinSurf, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground)
	{
		SDL_Color Background;
		Background.a = 0;
		Background.b = 0;
		Background.g = 0;
		Background.r = 0;
		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->GetTextImageCPU(Font, Text, DrawMode, Foreground, Background), NULL, WinSurf, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->GetTextImageCPU(Font, Text, DrawMode, Foreground, Background), NULL, WinSurf, &CopyTo);

	}
	void PushBuffer()
	{
		SDL_UpdateWindowSurface(Window);
	}

	void ClearAll()
	{
		ManagerGR->ClearPreLoadCPU(1.0);
		SDL_FreeSurface(WinSurf);
	}

};

class DrawGPU
{


	SDL_Rect CopyFrom;
	SDL_Rect CopyTo;
	SDL_Renderer *Render;
	SDL_Window* mainWindow;
	GraphicsManager* ManagerGR;
private:
	void InitOldCpp()
	{
		Render = NULL;
		ManagerGR = NULL;
	}



public:
	DrawGPU(GraphicsManager* ManagerGR, SDL_Renderer* Render, SDL_Window* mainWindow, EventingEngine* Events)
	{
		InitOldCpp();
		this->ManagerGR = ManagerGR;
		this->mainWindow = mainWindow;
		this->Render = Render;
		if (Render == NULL)
		{
			Events->GraphicsError("Renderer not initialized for DrawGPU.");
		}
	}

	~DrawGPU()
	{
		ClearAll();

	}

	void StartBuffer()
	{
		SDL_RenderClear(Render);
	}


	void AddToBuffer(int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source)
	{
		CopyFrom.h = OrigH;
		CopyFrom.w = OrigW;
		CopyFrom.x = OrigX;
		CopyFrom.y = OrigY;
		CopyTo.h = CopyH;
		CopyTo.w = CopyW;
		CopyTo.x = CopyX;
		CopyTo.y = CopyY;
		SDL_RenderCopy(Render, ManagerGR->LoaderGPU(Source), &CopyFrom, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->GetTextImageGPU(Font, Text, DrawMode, Foreground, Background), NULL, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Text, TextFont *Font, Mode DrawMode, SDL_Color Foreground)
	{
		SDL_Color Background;
		Background.a = 0;
		Background.b = 0;
		Background.g = 0;
		Background.r = 0;
		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->GetTextImageGPU(Font, Text, DrawMode, Foreground, Background), NULL, &CopyTo);

	}
	void AddToBuffer(int X, int Y, int W, int H, string Source)
	{

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->LoaderGPU(Source), NULL, &CopyTo);

	}
	void PushBuffer()
	{
		SDL_RenderPresent(Render);
	}



	void ClearAll()
	{
		ManagerGR->ClearPreLoadGPU(1.0);

	}
};

class DrawGL
{
	SDL_Window* mainWindow;
	GraphicsManager* ManagerGR;
	EventingEngine* EventEngine;
	SDL_GLContext ContextGL;
	int WinHeight, WinWidth;
private:
	void InitOldCpp()
	{
		mainWindow = NULL;
		ManagerGR = NULL;
		EventEngine = NULL;
	}
	bool GLErrorTest(string FuntionName)
	{
		GLenum Error = glGetError();
		if (Error != GL_NO_ERROR)
		{
			EventEngine->GraphicsError("OpenGL error in function " + FuntionName + " : " + to_string(static_cast<long long>(static_cast<int>(Error))));
			return false;
		}
		return true;
	}
	bool InitOpenGL()
	{
		ContextGL = SDL_GL_CreateContext(mainWindow);
		
		SDL_GL_MakeCurrent(mainWindow, ContextGL);

		SDL_GL_SetSwapInterval(1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);


		glClearColor(0, 0, 0, 0);

		glEnable(GL_TEXTURE_2D);

		glViewport(0, 0, WinWidth, WinHeight);

		glMatrixMode(GL_PROJECTION);

		glOrtho(0, WinWidth, WinHeight, 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();

		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glClear(GL_COLOR_BUFFER_BIT);

		return GLErrorTest("InitOpenGL()");

	}

	void AddToBufferFROMTEXTURE(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, GLuint TextureID, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
	{
		glTranslatef(X, Y, 0.0);

		glRotatef(AngleX, 1.0, 0.0, 0.0);
		glRotatef(AngleY, 0.0, 1.0, 0.0);
		glRotatef(AngleZ, 0.0, 0.0, 1.0);

		GLfloat Trg1Sz[] = {
							-W/2, -H/2, 0,
							-W/2,  H/2, 0,
							 W/2,  H/2, 0
						   };
		GLfloat Trg1Crd[] = {0,0 ,0,1 ,1,1};
		GLfloat Trg2Sz[] = {
							-W/2, -H/2, 0,
							 W/2, -H/2, 0,
							 W/2,  H/2, 0
						   };
		GLfloat Trg2Crd[] = {0,0 ,1,0 ,1,1};

		
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindTexture(GL_TEXTURE_2D, TextureID);

		glVertexPointer(3, GL_FLOAT, 0, &Trg1Sz);

		glTexCoordPointer(2, GL_FLOAT, 0, &Trg1Crd);

		glDrawArrays(GL_TRIANGLES, 0, 3);


		glVertexPointer(3, GL_FLOAT, 0, &Trg2Sz);

		glTexCoordPointer(2, GL_FLOAT, 0, &Trg2Crd);

		glDrawArrays(GL_TRIANGLES, 0, 3);


		glLoadIdentity();


		GLErrorTest("AddToBufferFROMTEXTURE()");
	} 
	void AddToBufferFROMPATH(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
	{
		GLuint TextureID = ManagerGR->LoaderGL(Path);
		AddToBufferFROMTEXTURE(X, Y, H, W, TextureID, AngleX, AngleY, AngleZ);
	}
	void AddToBufferFROMTEXT(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font,string Text,Mode DrawMode ,SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
	{
		GLuint TextureID = ManagerGR->GetTextImageGL(Font, Text, DrawMode, Foreground, Background);
		AddToBufferFROMTEXTURE(X, Y, H, W, TextureID, AngleX, AngleY, AngleZ);
	}
public:
	DrawGL(GraphicsManager* ManagerGR, SDL_Window* mainWindow,int Height, int Width, EventingEngine* Events)
	{
		InitOldCpp();
		this->ManagerGR = ManagerGR;
		this->mainWindow = mainWindow;
		this->EventEngine = Events;
		this->WinHeight = Height;
		this->WinWidth = Width;
		if (InitOpenGL() == false)
		{
			EventEngine->GraphicsError("OpenGL initialization error in function DrawGL().");
		}
	}
	~DrawGL()
	{
		ManagerGR->ClearPreLoadGL(1.0);
		SDL_GL_MakeCurrent(NULL, NULL);
		SDL_GL_DeleteContext(ContextGL);
	}
	void SetViewPort(int X, int Y, int Height, int Width)
	{
		glViewport(X, Y, Width, Height);
	}
	void StartBuffer()
	{
		
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(mainWindow);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
	{
		AddToBufferFROMPATH(X, Y, H, W, Path, AngleX, AngleY, AngleZ);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path, GLfloat AngleZ)
	{
		AddToBufferFROMPATH(X, Y, H, W, Path, 0, 0, AngleZ);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, string Path)
	{
		AddToBufferFROMPATH(X, Y, H, W, Path, 0, 0, 0);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
	{
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, AngleX, AngleY, AngleZ);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background, GLfloat AngleZ)
	{
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, AngleZ);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font, string Text, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
	{
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, 0);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font, string Text, Mode DrawMode, SDL_Color Background, GLfloat AngleX, GLfloat AngleY, GLfloat AngleZ)
	{
		SDL_Color Foreground;
		Foreground.a = 0;
		Foreground.b = 0;
		Foreground.r = 0;
		Foreground.g = 0;
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, AngleX, AngleY, AngleZ);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font, string Text, Mode DrawMode, SDL_Color Background, GLfloat AngleZ)
	{
		SDL_Color Foreground;
		Foreground.a = 0;
		Foreground.b = 0;
		Foreground.r = 0;
		Foreground.g = 0;
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, AngleZ);
	}
	void AddToBuffer(GLfloat X, GLfloat Y, GLfloat H, GLfloat W, TextFont* Font, string Text, Mode DrawMode, SDL_Color Background)
	{
		SDL_Color Foreground;
		Foreground.a = 0;
		Foreground.b = 0;
		Foreground.r = 0;
		Foreground.g = 0;
		AddToBufferFROMTEXT(X, Y, H, W, Font, Text, DrawMode, Foreground, Background, 0, 0, 0);
	}
	void PushBuffer()
	{
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		
		SDL_GL_SwapWindow(mainWindow);
	}
	void ClearAll()
	{
		ManagerGR->ClearPreLoadGL(1.0);
	}

};

struct WindowInfo
{
	int Height;
	int Width;
};


class GraphicsEngine
{
	

private:
	int Width, Height, LayerNumber;
	string Title;
	bool IsReady;
	bool IsStarted;
	SDL_Window* mainWindow;
	SDL_Renderer *Renderer;
	EventingEngine* EventEngine;
	GraphicsManager* ManagerGR;

	
	bool CPUInited;
	bool GLInited;
	bool GPUInited;
	vector<SDL_Surface*> PreLoadedSurfCPU;
	vector<SDL_Texture*> PreLoadedTextGPU;
	vector<string> PreLoadedPathsCPU;
	vector<string> PreLoadedPathsGPU;
private:
	void InitOldCpp()
	{
		Title = "Default";
		IsReady = false;
		IsStarted = false;
		mainWindow = NULL;
		Renderer = NULL;
		EventEngine = NULL;
		ManagerGR = NULL;
		CPUInited = false;
		GPUInited = false;
		GLInited = false;
	}
	

public:
	DrawCPU* DrawerCPU;
	DrawGPU* DrawerGPU;
	DrawGL* DrawerGL;


public:
	GraphicsEngine()
	{
		InitOldCpp();
	}
	GraphicsEngine(int Width, int Height, int LayerNumber, string Title, EventingEngine* Events)
	{
		InitOldCpp();
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->IsReady = true;
		this->EventEngine = Events;
		
	}
	void Init(int Width, int Height, int LayerNumber, string Title, EventingEngine* EvVar)
	{
		this->Width = Width;
		this->Height = Height;
		this->LayerNumber = LayerNumber;
		this->Title = Title;
		this->EventEngine = EvVar;
		this->IsReady = true;
		
	}

	bool Start()
	{
		if (IsReady == false)
		{
			EventEngine->GraphicsError("GraphicsEngine class is not initialized properly.");
			return false;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			EventEngine->GraphicsError(SDL_GetError());
			return false;
		}
		mainWindow = SDL_CreateWindow(Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (mainWindow == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());
			return false;
		}


		Renderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_ACCELERATED);
		if (Renderer == NULL)
		{
			EventEngine->GraphicsError(SDL_GetError());

		}
		if (TTF_Init() < 0)
		{
			EventEngine->GraphicsError(TTF_GetError());
		}

		int IMGFlags = IMG_INIT_PNG;
		int InitStat = IMG_Init(IMGFlags);
		if (InitStat != IMGFlags)
		{
			EventEngine->GraphicsError(IMG_GetError());
			return false;
		}
		



		
		this->ManagerGR = new GraphicsManager(EventEngine, Renderer);
		IsStarted = true;
		return true;
	}
	
	void InitCPU()
	{
		DrawerCPU = new DrawCPU(ManagerGR, mainWindow);
		CPUInited = true;
		
	}

	void DeleteCPU()
	{
		DrawerCPU->~DrawCPU();
		CPUInited = false;
	}

	void InitGPU()
	{
		DrawerGPU = new DrawGPU(ManagerGR, Renderer, mainWindow, EventEngine);
		
		GPUInited = true;
	}

	void DeleteGPU()
	{
		DrawerGPU->~DrawGPU();
		GPUInited = false;
	}
	void InitGL()
	{
		DrawerGL = new DrawGL(ManagerGR, mainWindow, Height, Width, EventEngine);
		GLInited = true;
	}
	void DeleteGL()
	{
		DrawerGL->~DrawGL();
		GLInited = false;
	}

	bool Stop()
	{
		
		SDL_DestroyWindow(mainWindow);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();

		if (CPUInited==true)
		{
			DeleteCPU();
		}
		if (GPUInited==true)
		{
			DeleteGPU();
		}
		if (GLInited==true)
		{
			DeleteGL();
		}

		
		IsStarted = false;
		return true;
	}
	void Delay(int Milliseconds)
	{
		SDL_Delay(Milliseconds);
	}

	WindowInfo getWindowSize()
	{
		WindowInfo Info;
		SDL_GetWindowSize(mainWindow, &Info.Width, &Info.Height);
		return Info;
	}

	
};


