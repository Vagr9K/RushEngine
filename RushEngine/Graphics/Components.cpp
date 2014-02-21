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


WindowInfo::WindowInfo()
{
	Height = 0;
	Width = 0;
	ZeroHeight = 0;
	ZeroWidth = 0;
	AspectX = 1.f;
	AspectY = 1.f;
}

bool RGBColor::operator==(RGBColor SecondObject)
{
	if (this->R == SecondObject.R && this->G == SecondObject.G && this->B == SecondObject.B && this->Fade == SecondObject.Fade)
		return true;
	return false;
}