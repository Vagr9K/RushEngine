#include "Interface.h"

void InterfaceBASE::AddToManager ()
        {
		ManagerDB->AddToCreate(InterElement);
	}
void InterfaceBASE::DeleteFromManager ()
        {
		ManagerDB->AddToDelete(InterElement);
	}
bool InterfaceBASE::CheckScreenZone (float x, float y, float h, float w, int MouseX, int MouseY)
        {

		float ActX = x;
		float ActY = y;
		h = h / 2;
		w = w / 2;
		if (((ActX - w) <= MouseX) && ((ActX + w) >= MouseX) && ((ActY + h) >= MouseY) && ((ActY - h) <= MouseY))
		{
			return true;
		}

		return false;
	}
void InterfaceBASE::StateTest ()
        {
		EventSystem->Input->Mouse->Refresh();
		if (CheckHover())
		{
			OnHover();
		}
		else if (CheckClick())
		{
			OnClick();
		}
		else
		{
			OnNULL();
		}
	}
InterfaceBASE::InterfaceBASE (ObjDBManager <InterfaceElement> * ManagerDB, EventingEngine * EventSystem)
        {
		this->ManagerDB = ManagerDB;
		this->EventSystem = EventSystem;
		InterElement = new InterfaceElement();
		InterElement->InterfacePtr = this;
		AddToManager();
		Inited = false;
	}
InterfaceBASE::~ InterfaceBASE ()
        {
		if (InterElement->TextExists)
		{
			delete InterElement->Text;
		}
		if (InterElement->ImageExists)
		{
			delete InterElement->Image;
		}
		delete InterElement;
		DeleteFromManager();
	}
void InterfaceBASE::Refresh ()
        {
		if (Inited == false)
		{
			Init();
		}
		StateTest();
	}

inline bool InterfaceBASE::CheckHover()
{

	int MouseX = EventSystem->Input->Mouse->Status.X;
	int MouseY = EventSystem->Input->Mouse->Status.Y;
	if (InterElement->ImageExists)
	{
		if (CheckScreenZone(InterElement->Image->x, InterElement->Image->y, InterElement->Image->h, InterElement->Image->w, MouseX, MouseY))
			return true;
	}
	if (InterElement->TextExists)
	{
		if (CheckScreenZone(InterElement->Text->x, InterElement->Text->y, InterElement->Text->h, InterElement->Text->w, MouseX, MouseY))
			return true;
	}
	return false;
}
inline bool InterfaceBASE::CheckClick()
{
	if (CheckHover())
	{
		if (EventSystem->Input->Mouse->Status.Motion == false)
		{
			if (EventSystem->Input->Mouse->Status.ButtonDOWN == LEFT)
				return true;
		}

	}
	return false;
}
inline void InterfaceBASE::OnHover()
{
	//Do nothing by default.
}
inline void InterfaceBASE::OnClick()
{
	//Do nothing by default.
}
inline void InterfaceBASE::OnNULL()
{

}
