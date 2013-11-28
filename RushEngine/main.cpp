#include "GameEngine.h"
#include <cstdlib>
#include <ctime>

int main(int argc, char** argv)
{
	b2Vec2 Gravity(0,10.0);
	
	b2World MainWorld(Gravity);
	GameEngine* mainEngine = new GameEngine;
	mainEngine->InitGraphics(680, 900, 2, "Title");
	mainEngine->Graphics->Start();
	mainEngine->Graphics->InitGPU();
	WindowInfo Info = mainEngine->Graphics->getWindowSize();
	
	SDL_Event e;
	int Oldx = 12;
	double NewX = rand()%Info.Width+0;
	double NewX2 = 0;
	int Oldy = 12;
	double NewY = rand() % Info.Height+0;
	double NewY2 =0;
	int Direct;

	int StartTime = GetTickCount();
	int Now = GetTickCount();
	int Delta=0;
	const int FPS = 60;
	 bool Die = false;
	while (Die == false)
	 {
		Now = GetTickCount();
		Delta = Now - StartTime;
		if (Delta>=(1/FPS*1000))
		{
			StartTime = GetTickCount();
			if (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
			{
				Die = true;

			}



			mainEngine->Graphics->DrawerGPU->StartBuffer();
			mainEngine->Graphics->DrawerGPU->AddToBuffer(static_cast<int>(NewX2), static_cast<int>(NewY2), 30, 30, "images/BlackInit.png");
			mainEngine->Graphics->DrawerGPU->AddToBuffer(static_cast<int>(NewX), static_cast<int>(NewY), 12, 12, "images/BlackInit.png");
			mainEngine->Graphics->DrawerGPU->PushBuffer();
			Direct = rand() % 10000;
			Direct -= 5000;
			NewX += Direct/1000;
			Direct = rand() % 20;
			Direct -= 10;
			NewX2 += Direct / 10;
			Direct = rand() % 10000;
			Direct -= 5000;
			NewY += Direct/1000;
			Direct = rand() % 20;
			Direct -= 10;
			NewY2 += Direct / 10;
			if (NewX > Info.Width)
			{
				NewX = 0;
			}
			if (NewX<0)
			{
				NewX = Info.Width;
			}
			if (NewY > Info.Height)
			{
				NewY = 0;
			}
			if (NewY<0)
			{
				NewY = Info.Height;
			}

			if (NewX2 > Info.Width)
			{
				NewX2 = 0;
			}
			if (NewX2<0)
			{
				NewX2 = Info.Width;
			}
			if (NewY2 > Info.Height)
			{
				NewY2 = 0;
			}
			if (NewY2 < 0)
			{
				NewY2 = Info.Height;
			}
		}
		
	 }

	 mainEngine->DeleteGraphics();
	
	return 0;
}