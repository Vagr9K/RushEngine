#include "DrawCPU.h"
void DrawCPU::InitOldCpp ()
        {
		Window = NULL;
		WinSurf = NULL;
		ManagerGR = NULL;
	}
DrawCPU::DrawCPU (GraphicsManager * ManagerGR, SDL_Window * mainWindow)
        {
		InitOldCpp();
		this->Window = mainWindow;
		this->ManagerGR = ManagerGR;
		WinSurf = SDL_GetWindowSurface(Window);

	}
DrawCPU::~ DrawCPU ()
        {
		ClearAll();

	}
void DrawCPU::StartBuffer ()
        {
		SDL_FillRect(WinSurf, NULL, SDL_MapRGB(WinSurf->format, 0, 0, 0));
	}
void DrawCPU::AddToBuffer (int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source)
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
void DrawCPU::AddToBuffer (int X, int Y, int W, int H, string Source)
        {

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->LoaderCPU(Source), NULL, WinSurf, &CopyTo);

	}
void DrawCPU::AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground)
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
void DrawCPU::AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
        {

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_BlitSurface(ManagerGR->GetTextImageCPU(Font, Text, DrawMode, Foreground, Background), NULL, WinSurf, &CopyTo);

	}
void DrawCPU::PushBuffer ()
        {
		SDL_UpdateWindowSurface(Window);
	}
void DrawCPU::ClearAll ()
        {
		ManagerGR->ClearPreLoadCPU(1.0);
		SDL_FreeSurface(WinSurf);
	}

