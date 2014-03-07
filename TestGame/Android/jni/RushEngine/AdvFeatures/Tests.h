#include <SDL.h>

class FPSTest
{
	double FPS;
	double StartTime;
	double Frames;
	double LastDiff;
	double MinDiffTime;
public:

	FPSTest(double MinDiffTime = 1000.0)
	{
		FPS = 0.0;
		Frames = 0.0;
		LastDiff = 0.0;
		this->MinDiffTime = MinDiffTime;
		StartTime = SDL_GetTicks();
		
	}
	void PushFrame()
	{
		Frames++;
	}
	double getFPS()
	{
		double EndTime = SDL_GetTicks();
		double DiffTime = EndTime - StartTime;
		if (DiffTime < MinDiffTime)
		{
			return FPS;
		}
		else
		{

			FPS = Frames / DiffTime * 1000;
			LastDiff = DiffTime;
			Frames = 0;
			StartTime = SDL_GetTicks();
			return FPS;
		}
	}
	double getLastDiff()
	{
		return LastDiff;
	}
};
