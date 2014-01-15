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
