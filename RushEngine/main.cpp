#include "GameEngineRAW.h"



int main(int argc, char** argv)
{
	GameEngine mainEngine("Name");
	 bool a = mainEngine.StartGraphics(450, 500, 4, "Dead Zone");
	 mainEngine.InitObjects(12, 12, 12, 12);
	 mainEngine.InitPhysics();
	 LayerElement* b;
	 for (int i = 0; i < 100000; i++)
	 {
		 b = new LayerElement;
		 b->Image = new IMG(12, 12, 12, 12, 12.12, "Source");
		 b->Text = new TXT(1, 2, 3, 4, 5, "String");
		 mainEngine.Objects->GrLayers[0].push_back(b);
		 b = NULL;
	 }
	 SDL_Event e;
	 OPSTester OPS;
	 bool Die = false;
	 while (Die == false)
	 {
		 
		 if(SDL_PollEvent(&e) != 0) 
		 if (e.type==SDL_QUIT)
		 {
			 Die = true;
			
		 }
		 
		 mainEngine.BlackInitGraphics();
		 OPS.TestOPS(10);
	 }
	mainEngine.StopGraphics();
	
	return 0;
}