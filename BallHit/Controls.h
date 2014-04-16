#include "GameEngine.h"

#include "Physics.h"

struct ControlManager
{
	BallManager* BallMan;
	MouseInput* InputDC;
	ControlManager(BallManager* BallMan)
	{
		this->BallMan = BallMan;
		InputDC = RushEngineInfo.Eventing->Input->Mouse;
	}

	void CheckInput()
	{
		InputDC->Refresh();
		if (InputDC->Status.Motion == false)
		{
			if (InputDC->Status.ButtonDOWN == LEFT)
			{
				float X = static_cast<float>(InputDC->Status.X);
				float Y = static_cast<float>(InputDC->Status.Y);
				BallMan->AddBall(X, Y);
			}
		}
	}
};