#include "ObjModel.h"

IMG::IMG ()
        {

	}
IMG::IMG (float x, float y, float w, float h, float Angle, string Source)
        {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->Angle = Angle;
		this->Source = Source;
	}
TXT::TXT ()
        {
		Font = NULL;
		Content = "No content was added!";
		DrawMode = SOLID;
	}
TXT::TXT (float x, float y, float w, float h, float Angle, TextFont * Font, Mode DrawMode, string Content)
        {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->Angle = Angle;
		this->Font = Font;
		this->Content = Content;
		this->DrawMode = DrawMode;
		Foreground = NULL;
		Background = NULL;
	}
ObjectElement::ObjectElement ()
        {
		TextExists = false;
		ImageExists = false;
		DrawFactor = 0.f;
		AllowDraw = true;
	}

ObjectElement::~ObjectElement()
{
	delete Image;
	delete Text;
}

Particle::Particle()
        {
		Active = false;
	}
EffectElement::EffectElement (EffectBASE * PtrToEffect, string Path)
        {
		this->PtrToEffect = PtrToEffect;
		this->Path = Path;
		ParticleCount = 0;
	}
EffectElement::~ EffectElement ()
        {
		delete[] ParticleArray;
	}
InterfaceElement::InterfaceElement ()
        {
		TextExists = false;
		ImageExists = false;
		Hidden = false;
		InterfacePtr = NULL;
	}

InterfaceElement::~InterfaceElement()
{
	delete Image;
	delete Text;
}

BackgroundElement::BackgroundElement()
        {
		TextExists = false;
		ImageExists = false;
		AllowDraw = true;
	}

