#include "DrawGPU.h"

void DrawGPU::InitOldCpp ()
        {
		Render = NULL;
		ManagerGR = NULL;
	}
DrawGPU::DrawGPU (GraphicsManager * ManagerGR, SDL_Renderer * Render, SDL_Window * mainWindow, EventingEngine * Events)
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
DrawGPU::~ DrawGPU ()
        {
		ClearAll();

	}
void DrawGPU::StartBuffer ()
        {
		SDL_RenderClear(Render);
	}
void DrawGPU::AddToBuffer (int OrigX, int OrigY, int OrigW, int OrigH, int CopyX, int CopyY, int CopyW, int CopyH, string Source)
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
void DrawGPU::AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground, SDL_Color Background)
        {

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->GetTextImageGPU(Font, Text, DrawMode, Foreground, Background), NULL, &CopyTo);

	}
void DrawGPU::AddToBuffer (int X, int Y, int W, int H, string Text, TextFont * Font, Mode DrawMode, SDL_Color Foreground)
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
void DrawGPU::AddToBuffer (int X, int Y, int W, int H, string Source)
        {

		CopyTo.h = H;
		CopyTo.w = W;
		CopyTo.x = X;
		CopyTo.y = Y;
		SDL_RenderCopy(Render, ManagerGR->LoaderGPU(Source), NULL, &CopyTo);

	}
void DrawGPU::PushBuffer ()
        {
		SDL_RenderPresent(Render);
	}
void DrawGPU::ClearAll ()
        {
		ManagerGR->ClearPreLoadGPU(1.0);

	}

