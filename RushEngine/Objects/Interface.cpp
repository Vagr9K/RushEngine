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