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

	this->StartTime = GetTickCount();
	this->MinDiff = 1 / RepeatsPerSecond;
}
bool OperationController::GetStatus()
{
	this->CurrentTime = GetTickCount();
	ULONGLONG Diff = CurrentTime - StartTime;
	if (Diff >= MinDiff)
	{
		StartTime = GetTickCount();
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

TextureRenderFactor::TextureRenderFactor()
{
	KX = 0;
	KY = 0;
}

