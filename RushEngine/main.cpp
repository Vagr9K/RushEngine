#include "GameEngine.h"




int main(int argc, char** argv)
{
	GameEngine mainEngine("Name");
	 bool a = mainEngine.StartGraphics(450, 500, 4, "Dead Zone");
	 SDL_Event e;
	 bool Die = false;
	 while (Die == false)
	 {
		 
		 if(SDL_PollEvent(&e) != 0) 
		 if (e.type==SDL_QUIT)
		 {
			 Die = true;
			
		 }
		 
		 mainEngine.BlackInitGraphics();
		 mainEngine.getEventSystem().LogError("FPS", "FPS");
	 }
	mainEngine.StopGraphics();
	
	return 0;
}