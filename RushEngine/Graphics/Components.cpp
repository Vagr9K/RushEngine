#include "Components.h"
void TextFont::InitOldCpp ()
        {
		PointSize=12;
		FontOutline =0;
		FontStyle = NORMAL;
		Index = 0;
		FontKerning = false;
	}
TextFont::TextFont (string FontPath)
        {
		InitOldCpp();
		this->FontPath = FontPath;

	}

OperationController::OperationController(int RepeatsPerSecond)  //TODO: Windows only!
{
	this->RepeatsPerSecond = RepeatsPerSecond;

	this->StartTime = GetTickCount64();
	this->MinDiff = 1 / RepeatsPerSecond;
}
bool OperationController::GetStatus()
{
	this->CurrentTime = GetTickCount64();
	int Diff = CurrentTime - StartTime;
	if (Diff >= MinDiff)
	{
		StartTime = GetTickCount64();
		return true;
	}
	else
	{
		return false;
	}
	return false;
}




