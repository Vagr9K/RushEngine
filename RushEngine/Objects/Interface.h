#include "ObjectManager.h"
#include "../Eventing/Eventing.h"
using namespace std;

class InterfaceBASE
{
	bool Inited;
private:
	void AddToManager()
	{
		ManagerDB->AddToCreate(InterElement);
	}
	void DeleteFromManager()
	{
		ManagerDB->AddToDelete(InterElement);
	}
protected:
	InterfaceElement* InterElement;
	ObjDBManager<InterfaceElement>* ManagerDB;
	EventingEngine* EventSystem;
protected:
	bool CheckScreenZone(float x, float y, float h, float w, int MouseX, int MouseY)
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
	inline virtual bool CheckHover()
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
	inline virtual bool CheckClick()
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

	virtual void Init() = 0;


	inline virtual void OnHover()
	{
		//Do nothing by default.
	}
	inline virtual void OnClick()
	{
		//Do nothing by default.
	}
	inline virtual void OnNULL()
	{

	}
	virtual void StateTest()
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
public:
	InterfaceBASE(ObjDBManager<InterfaceElement>* ManagerDB, EventingEngine* EventSystem)
	{
		this->ManagerDB = ManagerDB;
		this->EventSystem = EventSystem;
		InterElement = new InterfaceElement();
		InterElement->InterfacePtr = this;
		AddToManager();
		Inited = false;
	}
	~InterfaceBASE()
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
	void Refresh()
	{
		if (Inited == false)
		{
			Init();
		}
		StateTest();
	}

};