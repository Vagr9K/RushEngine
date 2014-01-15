#include "ObjectManager.h"
#include "../Eventing/Eventing.h"
using namespace std;


class InterfaceBASE
{
  bool Inited;
private:
  void AddToManager ();
  void DeleteFromManager ();
protected:
  InterfaceElement * InterElement;
  ObjDBManager <InterfaceElement> * ManagerDB;
  EventingEngine * EventSystem;
protected:
  bool CheckScreenZone (float x, float y, float h, float w, int MouseX, int MouseY);
  virtual bool CheckHover ();
  virtual bool CheckClick ();
  virtual void Init () = 0;
  virtual void OnHover ();
  virtual void OnClick ();
  virtual void OnNULL ();
  virtual void StateTest ();
public:
  InterfaceBASE (ObjDBManager <InterfaceElement> * ManagerDB, EventingEngine * EventSystem);
  ~ InterfaceBASE ();
  void Refresh ();
};
inline bool InterfaceBASE::CheckHover ()
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
inline bool InterfaceBASE::CheckClick ()
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
inline void InterfaceBASE::OnHover ()
        {
		//Do nothing by default.
	}
inline void InterfaceBASE::OnClick ()
        {
		//Do nothing by default.
	}
inline void InterfaceBASE::OnNULL ()
        {

	}
